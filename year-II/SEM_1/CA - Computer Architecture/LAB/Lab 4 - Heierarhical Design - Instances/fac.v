module fac (
  input x, y, ci,
  output co, z
);
  assign co = x&y | x&ci | y&ci;
  assign z = x ^ y ^ ci;
endmodule

module fac_tb;
  reg x, y, ci;
  wire co, z;
  
  fac inst (.x(x), .y(y), .ci(ci), .co(co), .z(z));

	integer k;
	initial begin
		$display("time\tx\ty\tci\tco\tz");
		$monitor("%0t\t%b\t%b\t%b\t%b\t%b", $time, x, y, ci, co, z);
		{x, y, ci} = 0;
		for (k = 1; k < 8; k = k + 1)
			#10 {x, y, ci} = k;
	end
endmodule