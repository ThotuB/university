module mux2s #(parameter w=8)(
  input [w-1:0] d0,d1,d2,d3,
  input [1:0] s,
  output reg [w-1:0] o
);
  always @(*) begin
    if (s == 0) o = d0;
    else if (s == 1) o = d1;
    else if (s == 2) o = d2;
    else o = d3;
  end
endmodule

module mux2s_tb; //w = 3
  reg [2:0] d0,d1,d2,d3;
  reg [1:0] s;
  wire [2:0] o;
  
  mux2s #(.w(3)) inst1(.d0(d0),.d1(d1),.d2(d2),.d3(d3),.s(s),.o(o));
  
  integer k;
  initial begin
    $display("time\ts\td0\td1\td2\td3\to");
    $monitor("%4t\t%b\t%b\t%b\t%b\t%b\t%b",$time,s,d0,d1,d2,d3,o);
    {s,d0,d1,d2,d3} = 0; //14 bits
    for (k=1; k<1000; k=k+1)
      #10 {s,d0,d1,d2,d3} = $urandom_range(1,16383);
    #10;
  end
endmodule
  