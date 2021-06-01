module d_ff(
    input clk, rst, set, d,
    output reg q
);
    always @ (posedge clk, posedge rst, posedge set) begin // posedge rst, posedge set not necessary but resets/sets on negedge of clock so output is not xxxxx 
        if ( set ) begin
            q <= 1;
        end else if ( rst ) begin
            q <= 0;
        end else begin
            q <= d; 
        end
    end
endmodule