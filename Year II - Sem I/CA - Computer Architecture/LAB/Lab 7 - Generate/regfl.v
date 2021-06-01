module regfl(
    input clk,rst_b,we,
    input [2:0] s,
    input [63:0] d,
    output [511:0] q
);
  wire [7:0] do;
  
  dec #(.w(3)) inst1(.s(s),.e(we),.o(do));
  
  generate
    genvar i;
    for (i=0; i<8; i=i+1) begin:rgst_instances
      rgst #(.w(64)) rgsts(.clk(clk),.rst_b(rst_b),.d(d),.clr(1'b0), .ld(do[i]),.q(q[511-64*i:448-64*i]));
    end
  endgenerate
endmodule

module regfl_tb;
  reg clk,rst_b,we;
  reg [2:0] s;
  reg [63:0] d;
  wire [511:0] q;
  
  regfl registerfile(.clk(clk),.rst_b(rst_b),.we(we),.s(s), .d(d),.q(q));
  
  localparam CLK_PERIOD=100, RUNNING_CYCLES=13, RST_DURATION=25;
  
  initial begin
    $display("time\tclk\trst_b\twe\ts\td\t\t\tq");
    $monitor("%4t\t%b\t%b\t%b\t%h\t%h\t%h",$time,clk,rst_b,we,s,d,q);
    clk=0;
    repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk=~clk;
  end
  
  initial begin
    rst_b=0;
    #RST_DURATION rst_b=~rst_b;
  end
  
  initial begin
    we=1;
    #(6*CLK_PERIOD) we=~we;
    #(1*CLK_PERIOD) we=~we;
  end
  
  task urand64(output reg [63:0] a);
    begin
      a[63:32]=$urandom;
      a[31:0]=$urandom;
    end
  endtask
  
  initial begin
    s=$urandom;
    urand64(d);
    repeat (12) begin
      #CLK_PERIOD;
      s=$urandom;
      urand64(d);
    end
  end
  
endmodule