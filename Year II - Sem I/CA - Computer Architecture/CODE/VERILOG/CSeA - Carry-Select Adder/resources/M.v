module M(
    input x, y,
    input sw,
    output z
);
    assign z = ( x & ~sw ) | ( y & sw );

endmodule