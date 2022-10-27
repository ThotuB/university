module mschdpath(
  input clk, rst_b,
  input ld_mreg, upd_mreg
  input[511:0] blk,
  output reg[31:0] m0
)

  function [31:0] MUX(input sw, input[31:0] d1, d0);
    if (sw) MUX = d1;
    else MUX = d0;
  endfunction

  function [31:0] RtRotate(input[31:0] x, input[4:0] p);
    reg[63:0] tmp;
    begin
      tmp = {x, x} >> p;
      RtRotate = tmp[31:0];
    end
  endfunction

  function [31:0] Sigma0(input[31:0] alpha);
    Sigma0 = RtRotate(alpha, 7) ^ RtRotate(alpha, 18) ^ (alpha >> 3);
  endfunction

  function [31:0] Sigma1(input[31:0] beta);
    Sigma1 = RtRotate(beta, 17) ^ RtRotate(beta, 19) ^ (beta >> 10);
  endfunction
  
  wire[31:0] m[16];
  generate
    genvar i;
    for (i = 1 ; i < 16 ; i = i + 1) begin:v
      if ( i < 15 )
        rgst #(.w(32)) gu(.clk(clk), ,rst_b(rst_b), .clr(1'b0), .ld(upd_mreg, .q(m[i]), .d(MUX(ld_mreg, blk[511-32*i : 480-32*i], m[i+1])));
      else
        rgst #(.w(32)) gu(.clk(clk), ,rst_b(rst_b), .clr(1'b0), .ld(upd_mreg, .q(m[i]), .d(MUX(ld_mreg, blk[511-32*i : 480-32*i], m[0] + Sigma0(m[1]) + m[9] + Sigma1(m[14]))));
    end
endmodule

module mschdpath_tb;
  reg clk, rst_b, ld_mreg, upd_mreg;
  reg[511:0] blk;
  wire[31:0] m0;
  
  mschdpath inst(.clk(clk), .rst_b(rst_b), .ld_mreg(ld_mreg), .upd_mreg(upd_mreg));
  
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