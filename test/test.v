module counter10#(
    parameter EFUSE_BIT  = 1024,
    parameter APB_ADDR_WIDTH  = 8,
    parameter APB_DATA_WIDTH  = 8
    )(
    input       wire        rstn,
    input       wire        clk,
    output      wire[3:0]   cnt,
    output      wire        cout,

    reg [3:0]               cnt_temp );

    always@(posedge clk or negedge rstn) begin
        if(! rstn)begin
            cnt_temp        <= 4'b0 ;
        end
        else if (cnt_temp==4'd9) begin
            cnt_temp        <=4'b000;
        end
        else begin
            cnt_temp        <= cnt_temp + 1'b1 ;
        end
    end

    assign  cout = (cnt_temp==4'd9) ;
    assign  cnt  = cnt_temp ;

    test#(
    .EFUSE_BIT(EFUSE_BIT),
    .APB_ADDR_WIDTH(APB_ADDR_WIDTH),
    .APB_DATA_WIDTH(APB_DATA_WIDTH)
    )test_01(
        .rstn(rstn),
        .clk(clk),
        .cnt(cnt),
        .cout(cout),
        .cnt_temp(cnt_temp)
    );

endmodule