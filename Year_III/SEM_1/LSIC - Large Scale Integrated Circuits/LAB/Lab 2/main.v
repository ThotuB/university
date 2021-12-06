module up_cntr_tb();
    reg clk, rst;
    reg [2:0] on_off;
    wire [15:0] cnt_up_ms; 
    
    up_cntr instanta(clk, rst, on_off, cnt_up);  
    
    initial begin 
        clk = 1; 
        forever #200 clk = ~clk;
    end

    initial begin 
        rst = 0;
        #1 rst = ~rst;
    end

    initial begin 
        on_off = 0;
        #1000 on_off = 3'b001;
        #10000 on_off = 3'b010;
        #1000 on_off = 3'b001; 
        #100000 on_off = 3'b011; 
        #3000000 $finish;
    end

    initial begin
        $dumpvars;
        $dumpfile("dump.vcd");
    end
endmodule