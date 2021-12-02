%c. Third Equation
disp('Third Equation: ');

x = 3.1:0.1:5;
myPlot(x, eqTrans_1c(x), zeros(size(x)));

xInterv = [3.1, 5]; % I:[a, b]

FatA = eqTrans_1c( xInterv(1) );
FatB = eqTrans_1c ( xInterv(2) );

if sign(FatA) ~= sign(FatB)
    [x] = fzero('eqTrans_1c', xInterv);
    display(x);
else
    disp('Solution not separated inside interval');
end