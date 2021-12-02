module BCD_C9(
    input[3:0] xi,
    output[3:0] xo
);
    assign xo[0] = ~xi[0];
    assign xo[1] = xi[1];
    assign xo[2] = xi[1] ^ xi[2];
    assign xo[3] = ~(xi[1] | xi[2] | xi[3]);
endmodule

module BCD_C9_tb;
    reg[3:0] xi;
    wire[3:0] xo;

    BCD_C9 inst(.xi(xi), .xo(xo));

    initial begin
        $display("xi3\txi2\txi1\txi0\t|\txi3\txi2\txi1\txi");
        $monitor("%b\t%b\t%b\t%b\t|\t%b\t%b\t%b\t%b", xi[3], xi[2], xi[1], xi[0], xo[3], xo[2], xo[1], xo[0]);
    end

    integer k;
    initial begin
        xi = 0;
        for ( k = 1 ; k < 10 ; k = k+1) begin
            #10 xi = k;
        end
    end
endmodule