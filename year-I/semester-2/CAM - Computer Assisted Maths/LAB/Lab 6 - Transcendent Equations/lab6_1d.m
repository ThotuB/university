%d. Fourth Equation
disp('Fourth Equation: ');
% give interval:
a = -5;
b = 10;

if a < b
    x = a:0.01:b;
    myPlot(x, (x - 3).^2, -5 + cos( abs( x )));
    myPlot(x, eqTrans_1d(x), zeros(size(x)));
    %this function should't have solutions on any interval

    xInterv = [a, b]; % I:[a, b]

    FatA = eqTrans_1d( a );
    FatB = eqTrans_1d( b );

    if sign(FatA) ~= sign(FatB)
        [x, fval] = fzero('eqTrans_1d', xInterv);
        display(x);
    else
        disp('Solution not separated inside interval');
    end
else
    disp('Interval not given correctly');
end
