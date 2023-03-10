module stimulus ();

   logic  clock;
   logic  In;
   logic  reset_b;
   
   logic  Out;
   
   integer handle3;
   integer desc3;
   


   // Instantiate DUT
   FSM dut (Out, reset_b, clock, In);

   // Setup the clock to toggle every 1 time units 
   initial 
     begin	
	clock = 1'b1;
	forever #5 clock = ~clock;
     end

   initial
     begin
	// Gives output file name
	handle3 = $fopen("test.out");
	// Tells when to finish simulation
	#500 $finish;		
     end

   always 
     begin
	desc3 = handle3;
	#5 $fdisplay(desc3, "%b %b || %b", 
		     reset_b, In, Out);
     end   
   
   initial 
     begin 

	#0  reset_b = 1'b0;
	#12 reset_b = 1'b1;	
     // Testing State 0
	#0  In = 1'b0;
	#10  In = 1'b1;
     // Testing State 2
     #10 In = 1'b1;
	#10 In = 1'b0;
     // Testing State 1, In = 1
     #10 In = 1'b1;
     // Returning to State 0, run back to State 1 to test In = 01
     #10 In = 1'b1;
     #10 In = 1'b0;
     // Testing State 1, In = 0
     #10 In = 1'b0;

     end

endmodule // FSM_tb

