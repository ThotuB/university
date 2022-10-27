module sha2indpath(
  input st_pkt, clr, pad_pkt, zero_pkt, mgln_pkt,
  input[63:0] pkt,
  output[2:0] idx,
  output[511:0] blk
);
  wire[63:0] a, b;
  
  pktmux packetmux(.pkt);
