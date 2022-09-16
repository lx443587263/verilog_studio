module adder(clk, rst_n, a, b, c);
	input [3:0] a;
	input [3:0] b;
	output [7:0] c;
	input clk, rst_n;

	wire [3:0] a;
	wire [3:0] b;
	reg [7:0] c;

	always @(posedge clk or negedge rst_n) begin
		if (rst_n == 1'b0)
			c <= 8'b0;
		else
			c <= a+b;
	end
endmodule

///home/liuxi/verible/verible-v0.0-2277-g8ab3c7e3/bin/test06.v