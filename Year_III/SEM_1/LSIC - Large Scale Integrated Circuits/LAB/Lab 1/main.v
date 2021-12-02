`timescale 1us/1ns

module design_tb();
    reg clk;
    reg rst;

    wire cnt_control;
    wire[7:0] output_ms;

    timer inst_1(
        .clk(clk),
        .rst(rst),
        .ms(cnt_control)
    );

    ms_counter inst_2(
        .clk(clk),
        .rst(rst),
        .ms_event(cnt_control),
        .cnt_ms(output_ms)
    );

    initial begin
        $display("cnt_control, \toutput_ms");
        $monitor("%d,\t%d", cnt_control, output_ms);
    end

    initial begin
        $dumpfile("dump.vcd");
        $dumpvars;
    end
    
    initial begin
        clk = 0;
        rst = 1;
        #800 rst = 0;
    end

    initial begin
        forever begin
            #400 clk = ~clk;
        end
    end
    
    initial begin
        #3000000 $finish;
    end
endmodule