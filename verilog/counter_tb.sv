module counter_tb;
    logic clk, rst;
    logic [7:0] q;
    counter dut (.*);

    initial forever #5 clk = ~clk;

    initial begin
        clk = 0; rst = 1;
        $dumpfile(`DUMPFILE);
        $dumpvars(0, counter_tb);
        @(negedge clk) rst = 0;
        repeat (10) @(negedge clk);
        assert (q == 10) else $fatal(1, "q = %0d, expected 10", q);
        $display("PASS");
        $finish;
    end
endmodule
