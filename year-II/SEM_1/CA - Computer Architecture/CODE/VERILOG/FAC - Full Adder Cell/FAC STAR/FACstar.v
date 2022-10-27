module FAC(
    input ci, x, y, 
    output z, p, co
);
    assign z = x ^ y ^ ci;
    assign p = x | y;
    assign co = (x & y) | (x & ci) | (y & ci);
endmodule