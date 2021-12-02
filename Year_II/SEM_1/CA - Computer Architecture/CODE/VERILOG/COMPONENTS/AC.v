module AC(
    input x, y, c,
    output z, p, g
);
    assign g = x & y;
    assign p = x | y;

    assign z = x ^ y ^ c;
endmodule