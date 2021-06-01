x=-10:0.01:10;
f = cos(x) + 0.6;
g = exp(sin(x));

plot(x, f, x, g);
[xs, ys] = ginput(2);

display(xs(1));
display(ys(1));
display(xs(2));
display(ys(2));
