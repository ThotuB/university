%a. First Equation
disp('First Equation: ');
x0 = 1;

xPlot = -6:0.1:6;
myPlot(xPlot, eqTrans_1a(xPlot), zeros(size(xPlot)));

[x] = fzero('eqTrans_1a', x0);

display(x);