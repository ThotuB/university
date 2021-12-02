module A(
    input x, y,
    output g, p
);
    assign g = x & y;
    assign p = x | y;
endmodule