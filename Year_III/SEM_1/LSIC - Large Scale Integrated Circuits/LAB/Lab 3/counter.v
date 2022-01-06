module counter(
    input clk,rst,
    output reg [15:0]cnt
);
    integer clk_circle_counter;

    always @ (posedge clk) begin
        if (rst) begin
            cnt <= 0;
            clk_circle_counter <= 0;
        end
        else begin
            clk_circle_counter <= clk_circle_counter + 1;

            if ((clk_circle_counter == 5000 && cnt != 0) || (clk_circle_counter == 4900 && cnt == 0)) begin
                cnt <= cnt+1;
                clk_circle_counter<=0;
            end
        end
    end
endmodule