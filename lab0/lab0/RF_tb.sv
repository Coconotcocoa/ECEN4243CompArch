module RF ();

   logic  clock;
   logic  write_enable3;
   logic  [4:0] read_address1;
   logic  [4:0] read_address2;
   logic  [4:0] write_address3;
   logic  [31:0] wide_data3;

   logic  [31:0] read_data1;
   logic  [31:0] read_data2;
   


   // Instantiate DUT
   regfile dut (clock, write_enable3, read_address1, read_address2, write_address3, wide_data3, read_data1, read_data2);

   // Setup the clock to toggle every 1 time units 
   initial 
     begin	
	clock = 1'b1;
	forever #5 clock = ~clock;
     end

   initial
     begin
	  #1000 $finish;		
     end

 
   
   initial 
    begin 
    // check if file writes when write enable is high     
	  #0  write_enable3 = 1'b0;
    #10 write_enable3 = 1'b1;
    #15 write_address3 = 5'b00110;
    #20  wide_data3 = 32'b010;
    #10 write_enable3 = 1'b0;
    #10 read_address1 = 5'b00110;
    #0 read_address2 = 5'b00110;
   
    // check if can write on clock edge
    #0 write_enable3 = 1'b1;
    #5 write_address3 = 5'b00010;
    #0  wide_data3 = 32'b001;
    #20 write_enable3 = 1'b0;
    #10 read_address1 = 5'b00010;
    #0 read_address2 = 5'b00110;
     
    // checks if $0 can be written to 
    #10 write_enable3 = 1'b1;
    #10 write_address3 = 5'b0;
    #5  wide_data3 = 32'b1000;
    #10 write_enable3 = 1'b0;
    #0 read_address1 = 5'b0;
    #0 read_address2 = 5'b0;
	

    end

endmodule // RF_tb

