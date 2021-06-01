%b. Second Equation
disp('Second Equation: ');
x0 = -3;
options = optimset('Tolx',10^(-6));


xPlot = -1.4:0.01:4;
myPlot(xPlot, eqTrans_1b(xPlot), zeros(size(xPlot)));

[x, fval,exitflag,output] = fzero('eqTrans_1b', x0 ,options);
iter = output.iterations;

display(x);
display(iter);