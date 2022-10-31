module HAC(
    input x, y,
    output z, c
);
    assign z = x ^ y;
    assign c = x & y;
endmodule