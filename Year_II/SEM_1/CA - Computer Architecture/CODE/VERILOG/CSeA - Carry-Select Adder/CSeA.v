module CSeA(
    input[7:0] x, y,
    input ci,
    output[7:0] z,
    output co
);
    wire[3:0] z1, z2;
    wire csw, co1, co2;

    RCA rcamain(.x(x[3:0]), .y(y[3:0]), .ci(ci), .z(z[3:0]), .co(csw));

    RCA rca1(.x(x[7:4]), .y(y[7:4]), .ci(1'b0), .z(z1[3:0]), .co(co1));
    RCA rca2(.x(x[7:4]), .y(y[7:4]), .ci(1'b1), .z(z2[3:0]), .co(co2));

    M mux4(.x(z1[0]), .y(z2[0]), .sw(csw), .z(z[4]));
    M mux5(.x(z1[1]), .y(z2[1]), .sw(csw), .z(z[5]));
    M mux6(.x(z1[2]), .y(z2[2]), .sw(csw), .z(z[6]));
    M mux7(.x(z1[3]), .y(z2[3]), .sw(csw), .z(z[7]));

    assign co = co1 | ( co2 & csw );
endmodule

module CSeA_tb;
    reg[7:0] x, y;
    reg ci;
    wire[7:0] z;
    wire co;

    CSeA inst(.x(x), .y(y), .ci(ci), .z(z), .co(co));

    initial begin
        $display("x\t   y\t    ci | co\tz");
        $monitor("%8b\t%8b\t%b  | %b  %8b", x, y, ci, co, z);
    end

    initial begin
        x = 157;
        y = 105;
        ci = 0;
    end

endmodule