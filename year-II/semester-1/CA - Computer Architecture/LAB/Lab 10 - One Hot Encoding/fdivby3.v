module fdivby3(
    input clr, c_up, clk, rst_b,
    output fdclk
);
    localparam S0 = 0;
    localparam S1 = 1;
    localparam S2 = 2;

    reg[2:0] st;
    wire[2:0] st_nxt;

    assign st_nxt[S0] = ( st[S0] & ( ~c_up | clr ) ) |
                        ( st[S1] & ( clr ) ) |
                        ( st[S2] & ( c_up | clr ) );

    assign st_nxt[S1] = ( st[S0] & ( c_up & ~clr ) ) |
                        ( st[S1] & ( ~c_up & ~clr ) );

    assign st_nxt[S2] = ( st[S1] & ( c_up | ~clr ) ) |
                        ( st[S2] & ( ~c_up & ~clr ) );

    assign fdclk = ( st[S0] );

    always @ (posedge clk, negedge rst_b) begin
        if ( !rst_b ) begin
            st <= 0;
            st[S0] <= 1;
        end else begin
            st <= st_nxt;
        end
    end

endmodule

module fdivby3_tb;
    reg clr, c_up, clk, rst_b;
    wire fdclk;

    fdivby3 inst( .clr(clr), .c_up(c_up), .clk(clk), .rst_b(rst_b), .fdclk(fdclk) );

    initial begin
        $display("time\tclk\trst_b\tclr\tc_up\td\tfdclk");
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
        clr = 0;
        #(4*CLK_PERIOD) clr = ~clr;
        #(1*CLK_PERIOD) clr = ~clr;
    end

    initial begin
        c_up = 1;
        #(6*CLK_PERIOD) c_up = ~c_up;
        #(1*CLK_PERIOD) c_up = ~c_up;
        #(4*CLK_PERIOD) c_up = ~c_up;
        #(2*CLK_PERIOD) c_up = ~c_up;
    end

endmodule