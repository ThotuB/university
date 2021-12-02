x0 = 0.5;

[xmin, fmin] = fminsearch('fct6', x0);

display(xmin);
display(fmin);

% plotting
x = -5:0.1:5;
plot(x, fct6(x), 'b');