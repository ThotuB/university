module BCD_C9(
    input[3:0] xi,
    output[3:0] xo
);
    assign xo[0] = ~xi[0];
    assign xo[1] = xi[1];
    assign xo[2] = xi[1] ^ xi[2];
    assign xo[3] = ~(xi[1] | xi[2] | xi[3]);
endmodule