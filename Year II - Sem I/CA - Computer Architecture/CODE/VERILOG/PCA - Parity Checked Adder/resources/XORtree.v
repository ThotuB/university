module XORtree(
    input[3:0] in,
    output p
);
    assign p = in[0] ^ in[1] ^ in[2] ^ in[3];
endmodule