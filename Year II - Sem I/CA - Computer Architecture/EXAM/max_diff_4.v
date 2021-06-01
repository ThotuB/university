module fac(
    input x, y, ci,
    output z, co
);

    assign z = x ^ y ^ ci;
    assign co = (x & y) | (x & ci) | (y & ci);
endmodule 

module add_sub_4(
    input [3:0] x, y,
    input s, d,
    output [3:0] z,
    output co
);
  
    wire [4:0] c;

    assign c[0] = s;
    generate
        genvar i;
        
        for (i = 0; i < 4; i=i+1) begin:arr
        fac inst(
            .x(x[i] ^ (d & s)),
            .y(y[i] ^ ((~d) & s)),
            .ci(c[i]),
            .z(z[i]),
            .co(c[i+1])
        );
        end
    endgenerate
    assign co = ~c[4];
endmodule


module max_diff_4(
    input[3:0] x, y, z
    output[3:0] o
);

endmodule