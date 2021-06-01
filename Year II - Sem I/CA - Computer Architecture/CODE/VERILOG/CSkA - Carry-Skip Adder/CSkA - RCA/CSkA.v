module CSkA(
    input[15:0] x, y,
    input ci,
    output[15:0] z,
    output co
);
    wire[3:0] c;

    assign c[0] = ci;
    RCA rca0(.x(x[3:0])  , .y(y[3:0])  , .ci(c[0]), .z(z[3:0])  , .co(c[1]));
    RCA rca1(.x(x[7:4])  , .y(y[7:4])  , .ci(c[1]), .z(z[7:4])  , .co(c[2]));
    RCA rca2(.x(x[11:8]) , .y(y[11:8]) , .ci(c[2]), .z(z[11:8]) , .co(c[3]));
    RCA rca3(.x(x[15:12]), .y(y[15:12]), .ci(c[3]), .z(z[15:12]), .co(co));

endmodule

module CSkA_tb;
    reg[15:0] x, y;
    reg ci;
    wire[15:0] z;
    wire co;

    CSkA inst(.x(x), .y(y), .ci(ci), .z(z), .co(co));

    initial begin
        $display("x\t\t   y\t\t    ci | co\tz");
        $monitor("%16b\t%16b\t%b | %b\t%16b", x, y, ci, co, z);
    end

    initial begin
        x = 3752;
        y = 21007;
        ci = 0;
    end
endmodule