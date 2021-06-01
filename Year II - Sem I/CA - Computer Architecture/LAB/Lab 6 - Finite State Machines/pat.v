module pat(
  input clk,
  input rst_b,
  input i,
  output o
);
  localparam S0_ST = 0;
  localparam S1_ST = 1;
  localparam S2_ST = 2;
  localparam S3_ST = 3;
  localparam S4_ST = 4;
  localparam S5_ST = 5;
  
  reg[2:0] st;
  reg[2:0] st_next;
  
  always @ (*)
    case (st)
      S0_ST:  if ( i == 0 ) st_next = S1_ST;
              else          st_next = S0_ST;
      S1_ST:  if ( i == 1 ) st_next = S2_ST;
              else          st_next = S1_ST;
      S2_ST:  if ( i == 0 ) st_next = S3_ST;
              else          st_next = S0_ST;
      S3_ST:  if ( i == 0 ) st_next = S4_ST;
              else          st_next = S2_ST;
      S4_ST:  if ( i == 1 ) st_next = S5_ST;
              else          st_next = S1_ST;
      S5_ST:  if ( i == 0)  st_next = S3_ST;
              else          st_next = S0_ST;
    endcase
  
  assign o = (st == S5_ST);
    
  always @ (posedge  clk, negedge rst_b)
    if ( !rst_b ) st <= S0_ST;
    else          st <= st_next;
  endmodule
  
  module pat_tb;
    reg clk, rst_b, i;
    wire o;
    
    pat inst(.clk(clk), .rst_b(rst_b), .i(i), .o(o)); 
    
    localparam CLK_PERIOD = 200;
    localparam RUNNING_CYCLES = 12;
    initial begin
      clk = 0;
      repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk = ~clk;
    end
    
    localparam RST_DURATION = 50;
    initial begin
      rst_b = 0;
      #RST_DURATION rst_b = 1;
    end
    
    initial begin
      i = 0;
      repeat (3) 
        #200 i = 1;
        #200 i = 0;
        #200 i = 1;
    end
  endmodule;
      