module r4b (
	input clk, 
	input rst_b,
	input ld,
	input [3:0] d,
	input sh,
	input sh_in,
	output [3:0] q
);
	always @ (posedge clk, negedge rst_b)
    if ( ! rst_b ) q <= 0;
    else if ( ld ) q <= d;
    else if ( sh ) q <= {sh_in, q[3:1]};
	end
endmodule
