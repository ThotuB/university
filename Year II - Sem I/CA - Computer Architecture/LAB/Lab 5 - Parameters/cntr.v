module cntr #(parameter w=8)(
  input clk,rst_b,c_up,c_dn,
  output reg [w-1:0] q
);
  always @ (posedge clk, negedge rst_b) begin
    if (rst_b == 0) q <= 0;
    else if (c_up == 1) q <= q+3;
    else if (c_dn == 1) q <= q-2;
  end
endmodule

module cntr_tb; //w = 3
  reg clk,rst_b,c_up,c_dn;
  wire [2:0] q;
  
  cntr #(.w(3)) inst1(.clk(clk),.rst_b(rst_b),.c_up(c_up),.c_dn(c_dn),.q(q));
  localparam CLK_PERIOD=20;
  localparam RUNNING_CYCLES=14;
  initial begin
    $display("time\tclk\trst_b\tc_up\tc_dn\tq");
    $monitor("%4t\t%b\t%b\t%b\t%b\t%b",$time,clk,rst_b,c_up,c_dn,q);
    clk=0;
    repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk=~clk;
  end
  localparam RST_DURATION=5;
  initial begin
    rst_b=0;
    #RST_DURATION rst_b=1;
  end
  initial begin
    c_up=1;
    #20 c_up=0;
    #20 c_up=1;
    #60 c_up=0;
    #60 c_up=1;
    #20 c_up=0;
  end
  initial begin
    c_dn=0;
    #20 c_dn=1;
    #40 c_dn=0;
    #100 c_dn=1;
  end
endmodule