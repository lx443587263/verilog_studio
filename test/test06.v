module counter110#(
    parameter EFUSE_BIT  = 1024,
    parameter APB_ADDR_WIDTH  = 8,
    parameter APB_DATA_WIDTH  = 8
    )(
    input[0:7]test,
    input[0:7]test,
    input[0:7]test,
    input[0:7]test,
    input[0:7]test,
    input[0:7]test,
    input[0:7]test,
    input[0:7]test,
    input       wire        rstn1,
    input       wire        clk1,
    output      wire[3:0]   cnt1,
    output      wire        cout1,

    reg [3:0]               cnt_temp1 );

    always@(posedge clk or negedge rstn) begin
        if(! rstn)begin
            cnt_temp        <= 4'b0 ;
        end
        else if (cnt_temp1==4'd9) begin
            cnt_temp1        <=4'b000;
        end
        else begin
            cnt_temp1        <= cnt_temp1 + 1'b1 ;
        end
    end


endmodule
