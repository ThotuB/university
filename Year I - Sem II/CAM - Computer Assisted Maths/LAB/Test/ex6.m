x = -5:0.001:5;
plot(x, func6(x), 'b');

g = @( x ) - func6(x);

[xmax1, fmax1] = fminbnd(g, -5, -3);
fprintf('maximum point: %g, maximum: %g\n', xmax1, -fmax1)

[xmax2, fmax2] = fminbnd(g, -0.5, 0);
fprintf('maximum point: %g, maximum: %g\n', xmax2, -fmax2)

[xmax3, fmax3] = fminbnd(g, 0, 4);
fprintf('maximum point: %g, maximum: %g\n', xmax3, -fmax3)

grid on;
