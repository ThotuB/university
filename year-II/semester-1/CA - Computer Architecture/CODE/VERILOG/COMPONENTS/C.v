module C(
    input Gij, Pij,
    input ci,
    output cj
);
    assign cj = Gij | ( Pij & ci );
endmodule