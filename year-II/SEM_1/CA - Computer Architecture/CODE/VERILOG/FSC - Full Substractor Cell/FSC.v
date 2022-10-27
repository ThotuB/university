module FSC(
    input bi, x, y, 
    output z, bo 
);
    assign z = x ^ y ^ bi;
    assign bo = (~x & y) | (~x & bi) | (y & bi);
endmodule

module FSC_tb;
    reg bi, x, y;
    wire z, bo;

    FSC inst(.bi(bi), .x(x), .y(y), .z(z), .bo(bo));

    initial begin
        $display("bi\tx\ty\t|\tbo\tz");
        $monitor("%b\t%b\t%b\t|\t%b\t%b", bi, x, y, bo, z);
    end

    integer k;
    initial begin
        {bi, x, y} = 0;
        for ( k = 1 ; k < 8 ; k = k+1)
            #10 {bi, x, y} = k;
    end
endmodule