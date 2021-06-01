% plotting
x = -6:0.001:6;
plot(x, fct7(x), 'b');

g = @( x ) - fct7(x);

[xmax1, fmax1] = fminbnd(g, -5.5, -4);
fprintf('maximum point: %g, maximum: %g\n', xmax1, -fmax1)

[xmin1, fmin1] = fminbnd('fct7', -1.5, -0.5);
fprintf('minimum point: %g, minimum: %g\n', xmin1, fmin1)

[xmax2, fmax2] = fminbnd(g, -0.5, 0);
fprintf('maximum point: %g, maximum: %g\n', xmax2, -fmax2)

[xmin2, fmin2] = fminbnd('fct7', -0.2, 0.2);
fprintf('minimum point: %g, minimum: %g\n', xmin2, fmin2)

[xmax3, fmax3] = fminbnd(g, 1, 3);
fprintf('maximum point: %g, maximum: %g\n', xmax3, -fmax3)

[xmin3, fmin3] = fminbnd('fct7', 3, 6);
fprintf('minimum point: %g, minimum: %g\n', xmin3, fmin3)




