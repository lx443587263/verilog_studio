module adder( in_asd, in_asd, in_asd, in_asd, in_asd, in_asd, in_asd, in_asd, in_asd,clk, rst_n, a, b, c);
    input in_asd;
    input in_asd;
    input in_asd;
    input in_asd;
    input in_asd;
    input in_asd;
    input in_asd;
    input in_asd;
    input in_asd;
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

	full_adder8 u_full_adder8(
		.a(c)
	);

    counter110 test_101(
        .in_asd( in_asd),
        .in_asd( in_asd),
        .in_asd( in_asd),
        .in_asd( in_asd),
        .in_asd( in_asd),
        .in_asd( in_asd),
        .in_asd( in_asd),
        .in_asd( in_asd),
        .in_asd( in_asd),
        .rstn11(rstn1),
        .clk1(clk1),
        .cnt1(cnt1),
        .cout1(cout1),
        .cnt_temp1()
    );

endmodule

