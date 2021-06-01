module PCA(
    input[3:0] x, y,
    input ci,
    input xp, yp,
    output[3:0] z, c,
    output co,
    output zp, cp,
    output err
);
    wire zpe;

    RCA rca(.x(x), .y(y), .ci(ci), .z(z), .c(c), .co(co));

    XORtree xortree_c(.in(c), .p(cp));
    assign zp = cp ^ xp ^ yp;

    XORtree xortree_z(.in(z), .p(zpe));
    assign err = zp ^ zpe;
endmodule

module PCA_tb;
    reg[3:0] x, y;
    reg ci;
    reg xp, yp;
    wire[3:0] z, c;
    wire co;
    wire zp, cp;
    wire err;

    PCA inst(.x(x), .y(y), .ci(ci), .xp(xp), .yp(yp), .z(z), .c(c), .co(co), .zp(zp), .cp(cp), .err(err));

    initial begin
        $display("x    y    c    z    | xp yp cp zp | ERROR");
        $monitor("%4b %4b %4b %4b | %b  %b  %b  %b  | %b", x, y, c, z, xp, yp, cp, zp, err);
    end

    initial begin
        x = 4'b0011;
        xp = 0;
        y = 4'b0011;
        yp = 0;
        ci = 0;
    end
endmodule