module counter #(parameter int W = 8) (
    input  logic         clk, rst,
    output logic [W-1:0] q
);
    always_ff @(posedge clk) q <= rst ? '0 : q + 1'b1;
endmodule
