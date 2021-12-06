module up_cntr(
    input clk, rst, 
    input [2:0] on_off, 
    output reg [15:0] cnt_up_ms  
);
    reg [15:0] cc_counter_reg, cc_counter_nxt;
    reg [15:0] cnt_up_ms_reg, cnt_up_ms_nxt;
    reg [2:0] state_reg, state_nxt; 

    localparam IDLE = 0;
    localparam NORMAL = 1;
    localparam STOP_COUNT_SAVE = 2;
    localparam STOP_COUNT_RESET = 3;

    always @ (posedge clk, negedge rst) begin 
        if (!rst) begin 
            cc_counter_reg <= 0; 
            cnt_up_ms_reg <= 0;
            state_reg <= IDLE;
        end
        else begin 
            cc_counter_reg <= cc_counter_nxt; 
            cnt_up_ms_reg <= cnt_up_ms_nxt;  
            state_reg <= state_nxt;
        end
    end
    
    always @ * begin 
        cc_counter_nxt = cc_counter_reg;
        cnt_up_ms_nxt = cnt_up_ms_reg;
        state_nxt = state_reg;
    
        case (state_reg)
            IDLE: begin 
                case (on_off) 
                    3'b001: state_nxt = NORMAL;
                    default: state_nxt = IDLE;
                endcase 
            end
            NORMAL: begin 
                if (cc_counter_reg == 4999) begin
                    cc_counter_nxt = 0;
                    cnt_up_ms_nxt = cnt_up_ms_reg + 1;
                end
                else begin 
                    cc_counter_nxt = cc_counter_reg + 1;
                end 
                
                case(on_off)
                    3'b010: state_nxt = STOP_COUNT_SAVE; 
                    3'b011: state_nxt = STOP_COUNT_RESET; 
                    default: state_nxt =  NORMAL;
                endcase
            end
            STOP_COUNT_SAVE: begin 
                state_nxt = IDLE; 
            end 
            STOP_COUNT_RESET: begin 
                cc_counter_nxt = 0; 
                cnt_up_ms_nxt = 0; 
                state_nxt = IDLE; 
            end 
        endcase
    end 
    
    assign cnt_up_ms = cnt_up_ms_reg;
endmodule