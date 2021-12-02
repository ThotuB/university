module BCDsub(
    input[3:0] x0, x1, x2, y0, y1, y2,
    output[3:0] z0, z1, z2
);
    wire[3:0] y0_C9, y1_C9, y2_C9;
    wire b01, b12, b23;

    BCD_C9 bcd9c0(.xi(y0), .xo(y0_C9));
    BCDadd bcdadd0(.x(x0), .y(y0_C9), .ci(1'b1)  , .co(b01), .z(z0));

    BCD_C9 bcd9c1(.xi(y1), .xo(y1_C9));
    BCDadd bcdadd1(.x(x1), .y(y1_C9), .ci(b01), .co(b12), .z(z1));

    BCD_C9 bcd9c2(.xi(y2), .xo(y2_C9));
    BCDadd bcdadd2(.x(x2), .y(y2_C9), .ci(b12), .co(b23), .z(z2));
endmodule

module BCDsub_tb;
    reg[3:0] x0, x1, x2, y0, y1, y2;
    wire[3:0] z0, z1, z2;

    BCDsub inst(.x0(x0), .x1(x1), .x2(x2), .y0(y0), .y1(y1), .y2(y2),
                .z0(z0), .z1(z1), .z2(z2));

    initial begin
        $display("X\tY\t|\tZ");
        $monitor("%d%d%d\t%d%d%d\t|\t%d%d%d", x2, x1, x0, y2, y1, y0, z2, z1, z0);
    end

    initial begin
        x2 = 7; x1 = 0; x0 = 3;
        y2 = 3; y1 = 8; y0 = 9;
    end
endmodule