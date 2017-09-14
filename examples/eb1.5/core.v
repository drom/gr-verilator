module core #(
  parameter W = 32,
  parameter S0 = 3'b000,
	parameter S1 = 3'b001,
	parameter S2 = 3'b010,
	parameter S3 = 3'b011,
	parameter S4 = 3'b100
)(
  input clk, reset_n,

  input  [W-1:0] t_dat,
  input          t_req,
  output         t_ack,

  output [W-1:0] i_dat,
  output         i_req,
  input          i_ack,

  output   [2:0] stt
);

// -------------------------------------------------------------------
// Elastic controller

wire sel, en0, en1;

// State machine
reg [2:0] state, nxt_state;

always @(posedge clk or negedge reset_n)
  if(~reset_n) state <= 0;
  else         state <= nxt_state;

always @(*)
  casez({state, t_req, i_ack})
    {S0, 2'b1?} : nxt_state = S1;

    {S1, 2'b01} : nxt_state = S0;
    {S1, 2'b10} : nxt_state = S2;
    {S1, 2'b11} : nxt_state = S3;

    {S2, 2'b?1} : nxt_state = S3;

    {S3, 2'b01} : nxt_state = S0;
    {S3, 2'b10} : nxt_state = S4;
    {S3, 2'b11} : nxt_state = S1;

    {S4, 2'b?1} : nxt_state = S1;

    default       nxt_state = state;
  endcase

assign sel = ((state == S3) | (state == S4));
assign en0 = t_req & ((state == S0) | (state == S3));
assign en1 = t_req &  (state == S1);

// acknowladge path
assign t_ack = ~((state == S2) | (state == S4));

// request path
assign i_req = ~(state == S0);

// -------------------------------------------------------------------
// data path
reg [W-1:0] dat0, dat1;

always @(posedge clk) if(en0) dat0 <= t_dat;
always @(posedge clk) if(en1) dat1 <= t_dat;

assign i_dat = sel ? dat1 : dat0;

assign stt = state;

endmodule
