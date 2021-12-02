module CLA(
    input[3:0] x, y,
    input cin,
    output[3:0] z,
    output[3:0] p, g,
    output cout
);
    wire[3:0] c;

    assign c[0] = cin;
    AC ac0(.x(x[0]), .y(y[0]), .c(c[0]), .z(z[0]), .p(p[0]), .g(g[0]));
    
    assign c[1] = g[0] | ( p[0] & c[0] );
    AC ac1(.x(x[1]), .y(y[1]), .c(c[1]), .z(z[1]), .p(p[1]), .g(g[1]));
    
    assign c[2] = g[1] | ( p[1] & c[1] );
    AC ac2(.x(x[2]), .y(y[2]), .c(c[2]), .z(z[2]), .p(p[2]), .g(g[2]));
    
    assign c[3] = g[2] | ( p[2] & c[2] );
    AC ac3(.x(x[3]), .y(y[3]), .c(c[3]), .z(z[3]), .p(p[3]), .g(g[3]));

    assign cout = g[3] | ( p[3] & c[3] );
endmodule

module CLA_tb;
    reg[3:0] x, y;
    reg cin;
    wire[3:0] z;
    wire[3:0] p, g;
    wire cout;

    CLA inst(.x(x), .y(y), .cin(cin),
            .z(z), .p(p), .g(g), .cout(cout));

    initial begin
        $display("x\ty\tci\t|\tco\tz\tp\tg");
        $monitor("%4b\t%4b\t%b\t|\t%b\t%4b\t%4b\t%4b", x, y, cin, cout, z, p, g);
    end

    initial begin
        x = 11;
        y = 2;
        cin = 0;
    end
endmodule