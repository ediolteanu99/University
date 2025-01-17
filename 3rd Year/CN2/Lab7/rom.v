module rom #(
        parameter   DATA_WIDTH = 16,
        parameter   ADDR_WIDTH = 8          // 2 * 1024 bytes of ROM
    )(
        input  wire                  clk,
        input  wire [ADDR_WIDTH-1:0] addr,  // here comes the program counter
        output  reg [DATA_WIDTH-1:0] data   // here goes the instruction
    );

    reg [DATA_WIDTH-1:0] value;

    always @* begin
        case (addr)
				/* DO NOT CHANGE THIS for task 1 and 2*/
				/*	 ldi 	r16, 1 		*/
				//0:		value = 16'b1110000000000001;
				/*	 out 	0x01, r16 		*/
				//1:		value = 16'b1011100100000001;
				/*	 sbi 	0x01, 1 		*/
				//2:		value = 16'b1001101000001001;
				/*	 cbi 	0x01, 0 		*/
				//3:		value = 16'b1001100000001000;
				/*	 in 	r17, 0x01 		*/
				//4:		value = 16'b1011000100010001;
						/*	 ldi 	r19, 255 		*/
				/*	 ldi 	r19, 255 		*/
		0:		value = 16'b1110111100111111;
		/*	 out 	0x01, r19 		*/
		1:		value = 16'b1011100100110001;
		/*	 ldi 	r20, 0 		*/
		2:		value = 16'b1110000001000000;
		/*	 out 	0x05, r20 		*/
		3:		value = 16'b1011100101000101;
		/*	 in 	r21, 0x04 		*/
		4:		value = 16'b1011000101010100;
		/*	 out 	0x02, r21 		*/
		5:		value = 16'b1011100101010010;
		/*	 rjmp 	loop 		*/
		6:		value = 16'b1100111111111101;
				/*	 ldi 	r20, 255 		*/
		//0:		value = 16'b1110111101001111;
		/*	 out 	0x01, r20 		*/
		//1:		value = 16'b1011100101000001;
		/*	 ldi 	r21, 0 		*/
		//2:		value = 16'b1110000001010000;
		/*	 out 	0x02, r21 		*/
		//3:		value = 16'b1011100101010010;
		/*	 sbi 	0x02, 7 		*/
		//4:		value = 16'b1001101000010111;
		/*	 sbi 	0x02, 0 		*/
		//5:		value = 16'b1001101000010000;
		/*	 cbi 	0x02, 7 		*/
		//6:		value = 16'b1001100000010111;
		/*	 cbi 	0x02, 0 		*/
		//7:		value = 16'b1001100000010000;
		/*	 sbi 	0x02, 6 		*/
		//8:		value = 16'b1001101000010110;
		/*	 sbi 	0x02, 1 		*/
		//9:		value = 16'b1001101000010001;
		/*	 cbi 	0x02, 6 		*/
		//10:		value = 16'b1001100000010110;
		/*	 cbi 	0x02, 1 		*/
		//11:		value = 16'b1001100000010001;
		/*	 sbi 	0x02, 5 		*/
		//12:		value = 16'b1001101000010101;
		/*	 sbi 	0x02, 2 		*/
		//13:		value = 16'b1001101000010010;
		/*	 cbi 	0x02, 5 		*/
		//14:		value = 16'b1001100000010101;
		/*	 cbi 	0x02, 2 		*/
		//15:		value = 16'b1001100000010010;
		/*	 sbi 	0x02, 4 		*/
		//16:		value = 16'b1001101000010100;
		/*	 sbi 	0x02, 3 		*/
		//17:		value = 16'b1001101000010011;
		/*	 cbi 	0x02, 4 		*/
		//18:		value = 16'b1001100000010100;
		/*	 cbi 	0x02, 3 		*/
		//19:		value = 16'b1001100000010011;
		/*	 sbi 	0x02, 3 		*/
		//20:		value = 16'b1001101000010011;
		/*	 sbi 	0x02, 4 		*/
		//21:		value = 16'b1001101000010100;
		/*	 cbi 	0x02, 3 		*/
		//22:		value = 16'b1001100000010011;
		/*	 cbi 	0x02, 4 		*/
		//23:		value = 16'b1001100000010100;
		/*	 sbi 	0x02, 2 		*/
		//24:		value = 16'b1001101000010010;
		/*	 sbi 	0x02, 5 		*/
		//25:		value = 16'b1001101000010101;
		/*	 cbi 	0x02, 2 		*/
		//26:		value = 16'b1001100000010010;
		/*	 cbi 	0x02, 5 		*/
		//27:		value = 16'b1001100000010101;
		/*	 sbi 	0x02, 1 		*/
		//28:		value = 16'b1001101000010001;
		/*	 sbi 	0x02, 6 		*/
		//29:		value = 16'b1001101000010110;
		/*	 cbi 	0x02, 1 		*/
		//30:		value = 16'b1001100000010001;
		/*	 cbi 	0x02, 6 		*/
		//31:		value = 16'b1001100000010110;
		/*	 sbi 	0x02, 0 		*/
		//32:		value = 16'b1001101000010000;
		/*	 sbi 	0x02, 7 		*/
		//33:		value = 16'b1001101000010111;
		default:		value = 16'b0000000000000000;


        endcase
    end

    always @(negedge clk) begin
        data <= value;
    end

endmodule
