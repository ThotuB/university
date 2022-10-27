module comb(
    input[3:0] i,
    output reg[4:0] o
);
    always @ (*) begin
        casez ( {i} )
            4'b0000:    o = 5'b01001;

            4'b0001:    o = 5'b00011;

            4'b0010:    o = 5'b11111;

            4'b0011:    o = 5'b11001;

            4'b0100:    o = 5'b01000;

            4'b0101:    o = 5'b00110;

            4'b0110:    o = 5'b01100;

            4'b0111:    o = 5'b01100;

            4'b1000:    o = 5'b00011;

            4'b1001:    o = 5'b00001;

            4'b1010:    o = 5'b01010;

            4'b1011:    o = 5'b00100;

            4'b1100:    o = 5'b00101;

            4'b1101:    o = 5'b11101;

            4'b1110:    o = 5'b01001;

            4'b1111:    o = 5'b01000;
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