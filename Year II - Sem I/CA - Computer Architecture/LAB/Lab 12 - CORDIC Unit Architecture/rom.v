module rom #(parameter aw=10, dw=32, file="rom_file.txt")(
    input clk, rst_b,
    input[aw-1:0] addr,
    output[dw-1:0] data
);
    reg [dw-1:0] mem[0:2**aw-1];
    
    initial begin
        $readmemh (file, mem, 0 , 2**aw - 1);
    end
    
    always @(posedgeclk, negedge rst_b) begin
        if ( !rst_b ) begin
            data <= 0;
        end else begin
            data <= mem [addr];
        end
    end

endmodule

module rom_tb;
    reg clk, rst_b;
    reg[3:0] addr;
    wire[15:0] data;

    rom #(.aw(4), .dw(16), .file("rom_file.txt")) inst(.clk(clk), .rst_b(rst_b), .bgn(bgn), .itr(itr), .ld(ld), .init(init), .fin(fin) );

    initial begin
        $display("time\tclk\trst_b\tbgn\titr\tld\tinit\tfin");
        $monitor("%4t\t%b\t%b\t%b\t%d\t%b\t%b\t%b", $time, clk, rst_b, bgn, itr, ld, init, fin);
    end

    // CLOCK
    localparam CLK_PERIOD = 100;
    localparam RUNNING_CYCLES = 17;
    initial begin
        clk = 0;
        repeat (2*RUNNING_CYCLES) #(CLK_PERIOD/2) clk = ~clk;
    end

    // RESET
    localparam RST_DURATION = 25;
    initial begin
        rst_b = 0;
        #RST_DURATION rst_b = 1;
    end

    // OTHER
    initial begin
        addr = 0;
        repeat (16)
          #(CLK_PERIOD) addr = addr + 1;
    end

endmodule