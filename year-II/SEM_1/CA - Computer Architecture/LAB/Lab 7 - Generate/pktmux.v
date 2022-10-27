module pktmux(
  input[63:0] msg_len, pkt,
  input pad_pkt, zero_pkt, mgln_pkt,
  output reg[63:0] o
);
  always @ (*)
    if ( pad_pkt )
      o = ( 1 << 63 );
    else if ( zerp_pkt )
      o = 0;
    else if ( mgln_pkt )
      o = msg_len;
    else
      o = pkt;
endmodule

module pktmux_tb;
  reg pad_pkt, zero_pkt, mgln_pkt;
  reg [63:0] pkt, msg_len;
  wire [63:0] o;
  
  pktmux inst(.msg_len(msg_len), .pkt(pkt), .pad_pkt(pad_pkt), .zero_pkt(zero_pkt) .mgln_pkt(mgln_pkt), .o(o));
  
  localparam ROUND = 100;
  initial  begin
    {pad_pkt, zero_pkt, mgln_pkt} = 0;
    repeat (3) begin
      #ROUND {pad_pkt, zero_pkt, mgln_pkt} = 4;
      #ROUND {pad_pkt, zero_pkt, mgln_pkt} = 2;
      #ROUND {pad_pkt, zero_pkt, mgln_pkt} = 1;
      #ROUND {pad_pkt, zero_pkt, mgln_pkt} = 0;
    end
  end
  
  task urand64(output reg [63:0] a);
    begin
      a[63:32] = $urandom;
      a[31:0]  = $urandom;
    end
  endtask
  
  initial begin
    urand64(pkt);
    urand64(msg_len);
    repeat (12) begin
      urand64(pkt);
      urand64(msg_len);
  end
endmodule
  