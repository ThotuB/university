module counter_tb();
    reg clk, rst;
    wire [15:0]cnt;

    up_counter ins(clk,rst,cnt);

    initial
        begin
        clk = 1;
        forever #1 clk = ~clk;
        #50 $finish;
    end

    initial begin
        rst = 1;
        #1;
        rst = ~rst;
        #3000000 $finish;
    end

    initial begin
        $dumpvars;
        $dumpfile("dump.vcd");
    end
endmodule