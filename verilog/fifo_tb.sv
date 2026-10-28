module fifo_tb;
    localparam W = 32;
    localparam N = 4;

    logic clk, rst;
    logic push, pop;
    logic [W-1:0] data_in;
    logic [N-1:0][W-1:0] data_out;
    logic [N-1:0] valid_out;

    logic [W-1:0] front;
    assign front = data_out[0];

    fifo #(.W, .N) dut(.clk, .rst, .push, .pop, .data_in, .data_out, .valid_out);

    initial forever #5 clk = ~clk;

    initial begin
        $dumpfile(`DUMPFILE);
        $dumpvars(0, fifo_tb);
        clk = 0; rst = 1; push = 0; pop = 0;
        @(negedge clk) rst = 0;

        // ========================================================================
        // FILL DRAIN
        // ========================================================================

        $info("begin: fill drain 1");
        // fill it: push 1, 2, 3, 4
        push = 1;
        for (int i = 1; i <= N; i++) begin
            data_in = i;
            @(negedge clk);
        end
        push = 0;


        // drain it: should come out 1, 2, 3, 4
        pop = 1;
        for (int i = 1; i <= N; i++) begin
            assert (front == i) else $warning("front = %0d, expected %0d", front, i);
            @(negedge clk);
        end
        pop = 0;

        // ========================================================================
        // FILL DRAIN
        // ========================================================================

        $info("begin: fill drain 2");
        // fill it: push 5 6 7 8 
        push = 1;
        for (int i = 1; i <= N; i++) begin
            data_in = i + N;
            @(negedge clk);
        end
        push = 0;


        // drain it: 
        pop = 1;
        for (int i = 1; i <= N; i++) begin
            assert (front == i + N) else $warning("front = %0d, expected %0d", front, i + N);
            @(negedge clk);
        end
        pop = 0;


        // ========================================================================
        // FILL FILL(POP SAME TIME)
        // ========================================================================

        $info("begin: fill fill");
        // fill it: push 1 2 3 4
        push = 1;
        for (int i = 1; i <= N; i++) begin
            data_in = i;
            @(negedge clk);
        end
        push = 0;

        // fill it: push 5 6 7 8
        push = 1;
        for (int i = 1; i <= N; i++) begin
            assert (front == i) else $warning("front = %0d, expected %0d", front, i);
            data_in = i + N;
            @(negedge clk);
        end
        push = 0;

        // drain it: 
        pop = 1;
        for (int i = 1; i <= N; i++) begin
            assert (front == i + N) else $warning("front = %0d, expected %0d", front, i + N);
            @(negedge clk);
        end
        pop = 0;

        // ========================================================================
        // SPARSE PUSH POP
        // ========================================================================
        $info("begin: sparse pop");

        // push 5, then push 6 and pop 5 in the same cycle
        push = 1; data_in = 5;
        @(negedge clk);
        pop = 1; data_in = 6;
        assert (front == 5) else $warning("front = %0d, expected 5", front);
        @(negedge clk);
        push = 0; pop = 0;
        assert (front == 6) else $warning("front = %0d, expected 6", front);

        $display("PASS");
        $finish;
    end
endmodule
