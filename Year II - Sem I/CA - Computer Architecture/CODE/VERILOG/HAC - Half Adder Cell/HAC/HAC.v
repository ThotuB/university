module HAC(
    input x, y,
    output z, c
);
    assign z = x ^ y;
    assign c = x & y;
endmodule

module HAC_tb;
    reg x, y;
    wire z, c;

    HAC inst(.x(x), .y(y), .z(z), .c(c));

    initial begin
        $display("x\ty\t|\tc\tz");
        $monitor("%b\t%b\t|\t%b\t%b", x, y, c, z);
    end

    integer k;
    initial begin
        {x, y} = 0;
        for ( k = 1 ; k < 4 ; k = k+1)
            #10 {x, y} = k;
    end
endmodule