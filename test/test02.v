module counter10#(
    parameter EFUSE_BIT  = 1024,
    parameter APB_ADDR_WIDTH  = 8,
    parameter APB_DATA_WIDTH  = 8
    )(
    input       wire        rstn,
    input       wire        clk,
    output      wire[3:0]   cnt,
    output      wire        cout,
    input	    wire	        a,
    input       wire            f,
    output reg [3:0]    cnt_temp
      
);
     always@(posedge clk or negedge rstn) begin
        if(! rstn)begin
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    wire test00001;
    
    
    
            cnt_temp        <= 4'b0 ;
        end
        else if (cnt_temp==4'd9) begin
            cnt_temp        <=4'b000;
        end
        else begin
            cnt_temp        <= cnt_temp + 1'b1 ;
        end
    end

    adder u_addr01(
        .in_test00001(test00001),
        
        .clk(clk),
        .rst_n(rstn),
        .a(a),
        .c(cout)
    );

    full_adder1 u_full_adder1(
        .out_test00001(test00001),
        
        .f(Ai)
    );

endmodule
