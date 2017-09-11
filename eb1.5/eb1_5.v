module eb1_5 #(
  parameter W = 32
)(
  input clk, reset_n,

  input  [W-1:0] t_dat,
  input          t_req,
  output         t_ack,

  output [W-1:0] i_dat,
  output         i_req,
  input          i_ack
);

reg  [6:0] state;
wire [6:0] state_next;

assign state_next = (
  (state[0] &  t_req) ? 7'b1000000 :
  (state[6] & ~t_req &  i_ack) ? 7'b0000001 :
  (state[6] &  t_req & ~i_ack) ? 7'b0000100 :
  (state[6] &  t_req &  i_ack) ? 7'b0000010 :
  (state[2] &  i_ack) ? 7'b0000010 :
  (state[1] & ~t_req &  i_ack) ? 7'b0000001 :
  (state[1] &  t_req & ~i_ack) ? 7'b0001000 :
  (state[1] &  t_req &  i_ack) ? 7'b1000000 :
  (state[3] &  i_ack) ? 7'b1000000 :
  state
);

always @(posedge clk or negedge reset_n)
  if (~reset_n) state <= 7'b1000000;
  else          state <= state_next;

assign i_req =  state[0];
assign t_ack = ~state[4];

wire sel, en0, en1;
reg  [W-1:0] dat0, dat1;

assign en0   = t_req & ~state[2];
assign en1   = t_req &  state[3];
assign sel   = state[0];

always @(posedge clk) if (en0) dat0 <= t_dat;
always @(posedge clk) if (en1) dat1 <= t_dat;

assign i_dat = sel ? dat1 : dat0;

endmodule
