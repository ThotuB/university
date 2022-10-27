y0 =[0; 0.2; -0.1];
interv = [0, 3];

[xval, yval] = ode113('eqdif9_3d', interv, y0)

plot(xval, yval);
legend('x', 'y', 'z');
hold on;

% 4-d. Approximation
vx = [0, 0.75, 1.1, 1.16, 2, 3];

vy = interp1(xval, yval, vx, 'pchip');

plot(vx, vy, 'ko');
display(vy);
legend('x', 'y', 'z');