module dec #(
  parameter w = 2
)(
	input [w-1:0] s,
    input en,
	output reg [2**w-1:0] o
);
	always @ (*) begin
		o = 0;
        if (en)
		    o[s] = 1;
	end
endmodule

module rgst #(
  parameter w = 8
)(
	input clk,rst_b,ld,clr,
	input [w-1:0] d,
	output reg [w-1:0] q
);
	always @ (posedge clk, negedge rst_b)
		if (!rst_b)   q <= 0;
		else if (clr)	q <= 0;
		else if (ld)		q <= d;
endmodule

module regfl(
    input clk, rst_b, en,
    input [2:0] s,
    input [12:0] d,
    output [90:0] q
    );
    wire [7:0] do;
    
    dec #(.w(3)) inst1(.s(s), .en(en), .o(do));
    
    generate
        genvar i;
        for (i=0; i<7; i=i+1) begin:v
            rgst #(.w(13)) gu(.clk(clk),.rst_b(rst_b),.d(d),.clr(1'b0), .ld(do[6-i]), .q(q[90-13*i:78-13*i]));
        end
    endgenerate
endmodule

module regfl_tb;
    reg clk, rst_b, en;
    reg [2:0] s;
    reg [12:0] d;
    wire [90:0] q;
    
    regfl registerfile(.clk(clk), .en(en), .rst_b(rst_b), .s(s), .d(d[12:0]), .q(q));
  
    initial begin
        $display("time\tclk\trst_b\ts\td\t\t\tq");
        $monitor("%4t\t%b\t%b\t%h\t%h\t%b",$time,clk,rst_b,s,d,q);
    end

    localparam CLK_PERIOD = 100;
    localparam RUNNING_CYCLES = 13;
    initial begin
        clk=0;
        repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk=~clk;
    end
    
    localparam RST_DURATION=25;
    initial begin
        rst_b=0;
        #RST_DURATION rst_b=~rst_b;
    end
    
    initial begin
        en = 1;
        s = 0;
        d = 'h11A7;
        #100
        s = 1;
        d = 'h1f3b;
        #100
        s = 2;
        d = 'h1bc;
        #100
        s = 3;
        d = 'h122c;
        #100
        s = 4;
        d = 'h96a;
        #100
        s = 5;
        d = 'h1247;
        #100
        s = 6;
        d = 'h410;
    end
  
endmodule