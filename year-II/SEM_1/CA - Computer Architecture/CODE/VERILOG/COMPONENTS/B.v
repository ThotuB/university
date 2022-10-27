module B(
    input Gjk, Pjk, Gij, Pij,
    output Gik, Pik
);
    assign Gik = Gjk | ( Pjk & Gij );
    assign Pik = Pjk & Pij;
endmodule