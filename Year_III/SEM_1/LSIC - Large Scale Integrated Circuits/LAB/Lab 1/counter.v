module timer(
    input clk, rst,
    output reg ms
);
    reg[12:0] cnt_reg, cnt_nxt;

    always @ (posedge clk) begin
        if (rst == 1) begin
            cnt_reg <= 0;
        end
        else begin
            cnt_reg <= cnt_nxt;
        end
    end

    always @ * begin
        ms = 0;
        cnt_nxt = cnt_reg + 1;

        if ( cnt_reg == 2500 ) begin
            cnt_nxt = 0;
            ms = 1'b1;
        end
    end
endmodule

module ms_counter(
    input clk, rst,
    input ms_event,
    output[7:0] cnt_ms
);
    reg[7:0] cnt_reg, cnt_nxt;

    always @ (posedge clk) begin
        if (rst == 1) begin
            cnt_reg <= 0;
        end
        else begin
            cnt_reg <= cnt_nxt;
        end
    end

    always @ * begin
        cnt_nxt = cnt_reg;
        
        if ( ms_event == 1 ) begin
            cnt_nxt = cnt_reg + 1;
        end
    end

    assign cnt_ms = cnt_reg;
endmodule