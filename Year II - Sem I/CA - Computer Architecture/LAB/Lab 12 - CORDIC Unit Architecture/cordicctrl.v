module cordicctrl(
    input clk, rst_b, bgn,
    input[3:0] itr,
    output ld, init, fin
);
    localparam WAIT = 0;
    localparam EXEC = 1;
    localparam END = 2;

    reg[2:0] st;
    wire[2:0] st_nxt;

    assign st_nxt[WAIT] =   ( st[WAIT] && ~bgn ) ||
                            ( st[END] );
    
    assign st_nxt[EXEC] =   ( st[WAIT] && bgn ) ||
                            ( st[EXEC] && itr != 15 );
    
    assign st_nxt[END] =   ( st[EXEC] && itr == 15 );

    assign ld = ( st[WAIT] && st_nxt[EXEC] ) ||
                ( st[EXEC] && st_nxt[EXEC] ) ||
                ( st[EXEC] && st_nxt[END] );

    assign init = ( st[WAIT] && st_nxt[EXEC] );

    assign fin = ( st[END] && st_nxt[WAIT] );

    always @ (posedge clk, negedge rst_b) begin
        if ( rst_b ) begin
            st <= 0;
            st[WAIT] <= 1;
        end else begin
            st <= st_nxt;
        end
    end
endmodule

module cordicctrl_tb;
    reg clk, rst_b, bgn;
    reg[3:0] itr;
    wire ld, init, fin;

    cordicctrl inst(.clk(clk), .rst_b(rst_b), .bgn(bgn), .itr(itr), .ld(ld), .init(init), .fin(fin) );

    initial begin
        $display("time\tclk\trst_b\tbgn\titr\tld\tinit\tfin");
        $monitor("%4t\t%b\t%b\t%b\t%d\t%b\t%b\t%b", $time, clk, rst_b, bgn, itr, ld, init, fin);
    end

    // CLOCK
    localparam CLK_PERIOD = 100;
    localparam RUNNING_CYCLES = 17;
    initial begin
        clk = 0;
        repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk = ~clk;
    end

    // RESET
    localparam RST_DURATION = 25;
    initial begin
        rst_b = 0;
        #RST_DURATION rst_b = 1;
    end

    // OTHER
    initial begin
        bgn = 1;
        #(CLK_PERIOD) bgn = 0;
    end
    
    initial begin
        itr = 0;
        repeat (16)
          #(CLK_PERIOD) itr = itr + 1;
    end

endmodule