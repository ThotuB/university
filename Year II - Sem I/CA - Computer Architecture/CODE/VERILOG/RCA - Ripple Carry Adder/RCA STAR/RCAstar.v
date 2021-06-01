module RCAstar(
    input[3:0] x, y,
    input ci,
    output[3:0] z,
    output co
    output P
);
    wire[3:0] c;
    wire[3:0] p;

    assign c[0] = ci;
    FACstar facstar0(.x(x[0]), .y(y[0]), .ci(c[0]), .z(z[0]), .p(p[0]), .co(c[1]));
    FACstar facstar1(.x(x[1]), .y(y[1]), .ci(c[1]), .z(z[1]), .p(p[1]), .co(c[2]));
    FACstar facstar2(.x(x[2]), .y(y[2]), .ci(c[2]), .z(z[2]), .p(p[2]), .co(c[3]));
    FACstar facstar3(.x(x[3]), .y(y[3]), .ci(c[3]), .z(z[3]), .p(p[3]), .co(co));

    assign P = p[0] & p[1] & p[2] & p[3];

endmodule