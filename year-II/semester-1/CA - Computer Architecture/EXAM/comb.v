module comb(
    input[3:0] i,
    output reg[5:0] o
);
    always @ (*) begin
        case ( i )
            4'b0000:    o = 6'b;

            4'b0001:    o = 6'b;

            4'b0010:    o = 6'b;

            4'b0011:    o = 6'b;

            4'b0100:    o = 6'b;

            4'b0101:    o = 6'b;

            4'b0110:    o = 6'b;

            4'b0111:    o = 6'b;

            4'b1000:    o = 6'b;

            4'b1001:    o = 6'b;

            4'b1010:    o = 6'b;

            4'b1011:    o = 6'b;

            4'b1100:    o = 6'b;

            4'b1101:    o = 6'b;

            4'b1110:    o = 6'b;

            4'b1111:    o = 6'b;
        endcase
    end

endmodule

module comb_tb;
    reg [3:0] i;
	wire [4:0] o;

	comb inst (.i(i), .o(o));

	integer k;
	initial begin
		$display("time\ti\to");
		$monitor("%0t\t%b\t%b", $time, i, o);
		i = 0;
		for (k = 1; k < 16; k = k + 1)
			#10 i = k;
	end
endmodule