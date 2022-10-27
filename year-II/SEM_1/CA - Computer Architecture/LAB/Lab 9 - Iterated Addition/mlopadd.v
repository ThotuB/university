module mlopadd(
  input clk, rst_b,
  input[7:0] x,
  output[31:0] a
);
  wire[7:0] reg1toadd;
  reg[31:0] addtoreg2;

  rgst #(.w(8)) reg1(.clk(clk), .rst_b(rst_b), .ld(1'b1), .clr(1'b0), .d(x), .q(reg1toadd));

  //always @ (posedge clk, negedge rst_b) begin
  //  if ( !rst_b ) addtoreg2 <= 0;
  //  else          addtoreg2 <= addtoreg2 + x;
  //end
  
  rgst #(.w(32)) reg2(.clk(clk), .rst_b(rst_b), .ld(1'b1), .clr(1'b0), .d(a + reg1toadd), .q(a));
endmodule

module mlopadd_tb;
  reg clk, rst_b;
  reg[7:0] x;
  wire[31:0] a;
  
  mlopadd inst(.clk(clk), .rst_b(rst_b), .x(x), .a(a));
  
  initial begin
    $display("time\tclk\trst_b\tx\ta");
    $monitor("%b\t%b\t%d\t%d", clk, rst_b, x, a);
  end
  
  localparam CLK_PERIOD = 100;
  localparam RUNNING_CYCLES = 100;
  
  initial begin
    clk = 0;
    repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk = ~clk;
  end
  
  localparam RST_DURATION = 25;
  
  initial begin
    rst_b = 0;
    #RST_DURATION rst_b = 1;
  end
  
  initial begin
    x = 1;
    while ( x < 200 )begin
      #CLK_PERIOD x = x + 2;
    end
  end
  
endmodule