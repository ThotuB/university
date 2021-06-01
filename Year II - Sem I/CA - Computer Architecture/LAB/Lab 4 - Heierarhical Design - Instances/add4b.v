module add4b (
  reg x[3:0], y[3:0], ci,
  wire co, z[3:0];
);
  wire c1, c2, c3

  fac inst0 (.x(x[0]), .y(y[0]), .ci(ci), .co(c1), .z(z[0]));
  fac inst1 (.x(x[1]), .y(y[1]), .ci(c1), .co(c2), .z(z[1]));
  fac inst2 (.x(x[2]), .y(y[2]), .ci(c2), .co(c3), .z(z[2]));
  fac inst3 (.x(x[3]), .y(y[3]), .ci(c3), .co(co), .z(z[3]));  
endmodule

module add4b_tb;
  reg x[3:0], y[3:0], ci;
  wire co, z[3:0];

  add4b inst (.x(x), .y(y), .ci(ci), .co(co), .z(z));

	integer k;
	initial begin
		$display("time\tx\ty\tci\tco\tz");
		$monitor("%0t\t%b\t%b\t%b\t%b\t%b", $time, x, y, ci, co, z);
		{x, y, ci} = 0;
		for (k = 1; k < 512; k = k + 1)
			#10 {x, y, ci} = k;
	end
endmodule