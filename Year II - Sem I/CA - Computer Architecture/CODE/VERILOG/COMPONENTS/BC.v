module BC(
    input Gjk, Pjk, Gij, Pij,
    input ci,
    output cj,
    output Gik, Pik
);
    assign Gik = Gjk | ( Pjk & Gij );
    assign Pik = Pjk & Pij;

    assign cj = Gij | ( Pij & ci );
endmodule