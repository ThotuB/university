x1 = -10:0.1:-5;
f1 = x1.^3 + 5;
x2 = -5:0.1:0;
f2 = sin(5.*x2) + cos(8.*x2);
x3 = 0:0.1:10;
f3 = x3.^3 + 5;

plot(x1, f1, 'b', x2, f2, 'r', x3, f3, 'b');