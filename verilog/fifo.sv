module fifo #(
    parameter W = 2, // width per entry
    parameter N = 2, // number of entries
    localparam N_bits = N > 1 ? $clog2(N) : 1 // max(log(n), 1)
)
(
    // signals
    input logic clk, rst,
    input logic push, pop,

    // input
    input logic [W-1:0] data_in,

    // output
    output logic [N-1:0] valid_out,
    output logic [N-1:0][W-1:0] data_out // 0 is front of queue
);

    typedef struct packed {
        logic [N_bits:0] len;   // [0,N]
        logic [N_bits-1:0] h, t;
        logic [N-1:0][W-1:0] q;
    } state_t;


    state_t s, n_s;

    // cross wiring
    // head -> [head, head+1, ...] 
    logic [N-1:0][N-1:0][W-1:0] out_mux;
    logic [N-1:0][N-1:0] valid_mux;
    always_comb begin
        for (int i = 0; i < N; i++) begin
            for (int j = 0; j < N; j++) begin
                logic left, right;
                logic [N_bits - 1:0] idx;

                idx = (i + j) % N; 
                left = s.h < s.t && (s.h <= idx && idx < s.t); 
                right = s.t < s.h && !(s.t <= idx && idx < s.h);

                valid_mux[i][j] = left || right || s.len == N;
                out_mux[i][j] = s.q[idx];
            end
        end
    end

    assign data_out = out_mux[s.h];
    assign valid_out = valid_mux[s.h];

    logic need_pop;
    always_comb begin
        n_s = s;

        need_pop = pop || (push && s.len == N);

        if (push) begin
            n_s.q[s.t] = data_in;
            n_s.t = (s.t != N - 1) ? s.t + 1 : 0; // (x+1)%n
        end

        if (need_pop) begin
            n_s.h = (s.h != N - 1) ? s.h + 1 : 0; // (x+1)%n
        end

        if (push && !need_pop) begin
            n_s.len = s.len + 1;
        end else if (!push && need_pop) begin
            n_s.len = s.len - 1;
        end
    end

    always_ff @(posedge clk) begin 
        if (rst) begin
            s <= '0;
        end else begin
            s <= n_s;

            assert (!(s.len == 0 && !push && pop)) else $warning("pop when len=0");
        end
    end

    
endmodule

