module RCA(
    input[3:0] x, y,
    input ci,
    output[3:0] z,
    output[3:0] c,
    output co
);
    assign c[0] = ci;
    FAC fac0(.x(x[0]), .y(y[0]), .ci(c[0]), .z(z[0]), .co(c[1]));
    FAC fac1(.x(x[1]), .y(y[1]), .ci(c[1]), .z(z[1]), .co(c[2]));
    FAC fac2(.x(x[2]), .y(y[2]), .ci(c[2]), .z(z[2]), .co(c[3]));
    FAC fac3(.x(x[3]), .y(y[3]), .ci(c[3]), .z(z[3]), .co(co));

endmodule