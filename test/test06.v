module counter110#(
    parameter EFUSE_BIT  = 1024,
    parameter APB_ADDR_WIDTH  = 8,
    parameter APB_DATA_WIDTH  = 8
    )(
     //group a
     input       wire        in_test00001,
     //end group a
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
