module cons(
    input clk, rst_b,
    input val,
    input[7:0] data,
    output reg[7:0] sum
);
    always @ (posedge clk, negedge rst_b) begin
        if ( !rst_b ) begin
            sum <= 0;
        end else begin
           if ( val ) begin
               sum <= sum + data;
           end 
        end
    end
endmodule

module cons_tb;
    reg clk, rst_b;
    wire val;
    wire[7:0] data, sum;

    prod producer(.clk(clk), .rst_b(rst_b), .val(val), .data(data));
    cons consumer(.clk(clk), .rst_b(rst_b), .val(val), .data(data), .sum(sum));

    localparam CLK_PERIOD = 100;
    localparam RUNNING_CYCLES = 100;

    initial begin
        $display("time\tclk\trst_b\tval\tdata\tsum");
        $monitor("%5t\t%b\t%b\t%b\t%1d\t%1d", $time, clk, rst_b, val, data, sum);
    end

    initial begin
        clk = 0;
        repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk = ~clk;
    end

    localparam RST_DURATION = 25;

    initial begin
        rst_b = 0;
        #RST_DURATION rst_b = 1;
    end
endmodule