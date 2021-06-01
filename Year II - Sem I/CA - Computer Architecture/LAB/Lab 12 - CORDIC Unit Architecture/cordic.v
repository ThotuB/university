module cordic(
    input clk, rst_b, bgn,
    input[15:0] theta,
    output[15:0] cos,
    output fin
);
    function [15:0] MUX(input s, input [15:0] d1, d0);
        begin
            MUX = ( s ) ? d1 : d0;
        end
    endfunction

    function [15:0] ArRSh(input [15:0] i, input [3:0] pos);
        reg[31:0] temp;
        begin
            temp = {{16{i[15]}}, i} >> pos;
            ArRSh = temp[15:0];
        end
    endfunction
    
    function [15:0] AddSub(input add, input [15:0] a, b);
        begin
            AddSub = MUX(add, a+b, a-b);
        end
    endfunction

    wire [15:0] q_TO_i_AND_a1, q_TO_i_AND_a2;
    wire [15:0] data_TO_b, q_TO_a;
    wire [3:0] itr;
    wire ld, init;

    rgst # (.w(16)) i0 (.clk(clk), .rst_b(rst_b), .ld(ld), .clr(0), .q(q_TO_i_AND_a1),
                        .d( MUX(init, 16'h26dd, AddSub(q_TO_a[15], q_TO_i_AND_a1, ArRSh(q_TO_i_AND_a2, itr) ) ) ) );



endmodule