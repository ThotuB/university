y0 = [0.5; -0.5; 0.3];
interv = [1, 4];

[xval, yval] = ode113('eqdif9_3c', interv, y0);

plot(xval, yval(:, 1));
hold on;

% 4-c. Approximation
vx = [1, 2.2, 3.5, 4];

vy = interp1(xval, yval(:, 1), vx, 'pchip');

plot(vx, vy, 'ko');
display(vy);