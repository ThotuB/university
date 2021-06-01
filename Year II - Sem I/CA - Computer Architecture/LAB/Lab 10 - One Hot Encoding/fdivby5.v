module fdivby5(
    input clr, c_up, clk, rst_b,
    output fdclk
);
    wire[2:0] d, q;

    rgst #( .w(3) ) register (.clk(clk), .rst_b(rst_b), .ld(c_up), .clr(clr | q[2]), .d(d), .q(q));

    assign d[2] = ( q[2] ^ ( q[1] & q[0] ) );
    assign d[1] = ( q[1] ^ q[0] );
    assign d[0] = ~q[0];

    assign fdclk = ~(q[2] | q[1] | q[0]);
endmodule

module fdivby5_tb;
    reg clr, c_up, clk, rst_b;
    wire fdclk;

    fdivby5 inst( .clr(clr), .c_up(c_up), .clk(clk), .rst_b(rst_b), .fdclk(fdclk) );

    initial begin
        c_up = 1;
        $display("time\tclk\trst_b\tclr\tc_up\tfdclk");
        $monitor("%4t\t%b\t%b\t%b\t%b\t%d", $time, clk, rst_b, c_up, c_up, fdclk);
    end

    localparam CLK_PERIOD = 100;
    localparam RUNNING_CYCLES = 50;
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
        c_up = 1;
        clr = 0;
        #(6*CLK_PERIOD) clr = ~clr;
        #(1*CLK_PERIOD) clr = ~clr;
        #(5*CLK_PERIOD) clr = ~clr;
        #(1*CLK_PERIOD) clr = ~clr;
    end

endmodule