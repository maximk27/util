module adder #(
    parameter W=2
) (
    input logic [W-1:0] a, b,
    output logic [W:0] c
);

    assign c = a + b;
endmodule;
