y0 = [-1; 2];
interv = [0, 6];

[xval, yval] = ode113('eqdif9_3b', interv, y0);

plot(xval, yval(:, 1));
hold on;

% 4-b. Approximation
vx = [0, 1.5, 2.3, 3.7, 4, 5.45];

vy = interp1(xval, yval(:, 1), vx, 'pchip');

plot(vx, vy, 'ko');
display(vy);