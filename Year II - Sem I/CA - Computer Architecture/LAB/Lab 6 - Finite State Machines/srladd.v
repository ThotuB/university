module pat(
  input clk,
  input rst_b,
  input x,
  input y,
  output z
);
  localparam S0_ST = 0;
  localparam S1_ST = 1;
  
  reg st;
  reg st_next;
  
  always @ (*)
    case (st)
      S0_ST:  if ( {x, y} == 3 )  st_next = S1_ST;
              else                st_next = S0_ST;
      S1_ST:  if ( {x, y} == 0 )  st_next = S0_ST;
              else                st_next = S1_ST;
    endcase
  
  assign z = x ^ y ^ st;
    
  always @ (posedge  clk, negedge rst_b)
    if ( !rst_b ) st <= S0_ST;
    else          st <= st_next;
  endmodule
  
  module pat_tb;
    reg clk, rst_b, x, y;
    wire z;
    
    pat inst(.clk(clk), .rst_b(rst_b), .x(x), .y(y), .z(z)); 
    
    localparam CLK_PERIOD = 50;
    localparam RUNNING_CYCLES = 5;
    initial begin
      clk = 0;
      repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk = ~clk;
    end
    
    localparam RST_DURATION = 10;
    initial begin
      rst_b = 0;
      #RST_DURATION rst_b = 1;
    end
    
    initial begin
      x = 0;
      repeat (5) 
        #CLK_PERIOD x = ~x;
    end
    
    initial begin
      y = 0;
      repeat (2) 
        #(2*CLK_PERIOD) y = ~y;
    end
    
  endmodule;
      
