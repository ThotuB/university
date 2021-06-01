module ex1 (
	input a, b, c, d,
	output f1, f2, f3, f4, f5
);
  assign f1 = 0;
	assign f2 = (a & (~b)) | (b & d) | (~c & d);
	assign f3 = (~c & ~d) | (b & d);
	assign f4 = (~c & d) | (b & ~c) | (a & b);
	assign f5 = (~a & d) | (~b & d) | (b & ~d);
endmodule

module ex1_tb;
	reg a, b, c, d;
	wire f1, f2, f3, f4, f5;

	ex1b inst (.a(a), .b(b), .c(c), .d(d), .f1(f1), .f2(f2), .f3(f3), .f4(f4), .f5(f5));

	integer k;
	initial begin
		$display("time\ta\tb\tc\td\ti_int\tf1\tf2\tf3\tf4\tf5");
		$monitor("%0t\t%b\t%b\t%b\t%b\t%0d\t%b\t%b\t%b\t%b\t%b", $time, a, b, c, d, {a,b,c,d}, f1, f2, f3, f4, f5);
		{a, b, c, d} = 0;
		for (k = 1; k < 16; k = k + 1)
			#10 {a, b, c, d} = k;
	end
endmodule