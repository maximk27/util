module adder_tb;
    localparam W = 32;

    logic [W-1:0] a, b;
    logic [W:0] c;
    adder #(.W) dut (.a, .b, .c);

    initial begin
        $dumpfile(`DUMPFILE);
        $dumpvars(0, adder_tb);

        a = 4; b = 3; #1;
        assert(c == 7) else $fatal(1, "not 7");

        a = 2; b = 3; #1;
        assert(c == 5) else $fatal(1, "not 5");


        $display("PASS");
        $finish;
    end


endmodule
