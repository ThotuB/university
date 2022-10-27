module FAC(
    input ci, x, y, 
    output z, co 
);
    assign z = x ^ y ^ ci;
    assign co = (x & y) | (x & ci) | (y & ci);
endmodule

module FAC_tb;
    reg ci, x, y;
    wire z, co;

    FAC inst(.ci(ci), .x(x), .y(y), .z(z), .co(co));

    initial begin
        $display("c\tx\ty\t|\tc\tz");
        $monitor("%b\t%b\t%b\t|\t%b\t%b", ci, x, y, co, z);
    end

    integer k;
    initial begin
        {ci, x, y} = 0;
        for ( k = 1 ; k < 8 ; k = k+1)
            #10 {ci, x, y} = k;
    end
endmodule