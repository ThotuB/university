module prod(
  input clk,
  input rst_b,
  output reg val,
  output reg[7:0] data
);
  integer cnt;

  always @ (posedge clk, negedge rst_b) begin
    if ( !rst_b ) begin
      val <= 0;
      cnt <= 1;
    end else begin
      cnt <= cnt - 1;
      if ( cnt == 1 ) begin
        val <= ~val;
        if ( val )
          cnt <= $urandom_range(1,4);
        else
          cnt <= $urandom_range(3, 5);
          data <= $urandom_range(0, 5);
      end
      if ( val )
        data <= $urandom_range(0, 5);
    end
  end
endmodule

module prod_tb;
  reg clk, rst_b;
  wire val;
  wire[7:0] data;

  prod producer(.clk(clk), .rst_b(rst_b), .val(val), .data(data));

  localparam CLK_PERIOD = 100;
  localparam RUNNING_CYCLES = 100;

  initial begin
    $display("time\tclk\trst_b\tval\tdata");
    $monitor("%5t\t%b\t%b\t%b\t%1d", $time, clk, rst_b, val, data);
  end

  initial begin
    clk = 0;
    repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk = ~clk;
  end

  localparam RST_DURATION = 25;

  initial begin
    rst_b = 0;
    #RST_DURATION rst_b = 1;
  end
endmodule