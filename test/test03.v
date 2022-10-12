module adder( combo, combo, combo, combo, combo, combo_dbg, combo, combo_dbg_out,clk, rst_n, a, b, c);
    output [1:0] combo_dbg_out;
    wire [1:0] combo;
    output combo_dbg;
    wire [1:0] combo;
    wire [1:0] combo;
    wire [1:0] combo;
    wire [1:0] combo;
    wire [1:0] combo;
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
        . combo( combo),

        . combo( combo),

        . combo( combo),

        . combo( combo),

        .combo_dbg( combo_dbg),

        . combo( combo),

        . combo_dbg_out( combo_dbg_out),

        .rstn11(rstn1),
        .clk1(clk1),
        .cnt1(cnt1),
        .cout1(cout1),
        .cnt_temp1()
    );

endmodule

