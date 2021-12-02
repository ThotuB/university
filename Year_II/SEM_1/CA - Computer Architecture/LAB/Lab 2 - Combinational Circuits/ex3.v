module ex3 (
	input [3:0] i,
	output [3:0] o
);
	assign o[3] = i[3] | i[2]&i[0] | i[2]&i[1];
	assign o[2] = ~i[2]&i[0] | ~i[2]&i[1] | i[2]&~i[1]&~i[0];
	assign o[1] = i[0] ^ i[1];
	assign o[0] = i[0];
endmodule

module ex3_tb;
	reg [3:0] i;
	wire [3:0] o;

	ex3 inst (.i(i), .o(o));

	integer k;
	initial begin
		$display("time\ti\to");
		$monitor("%0t\t%b\t%b", $time, i, o);
		i = 0;
		for (k = 1; k < 16; k = k + 1)
			#10 i = k;
	end
endmodule