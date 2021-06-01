y0 = 2;
interv = [-1, 5];

[xval, yval] = ode23('eqdif9_3a', interv, y0);

plot(xval, yval);
hold on;

% 4-a. Approximation
%vx = [-1, -0.5, 0, 1, 2.3, 5];

%vy = interp1(xval, yval, vx, 'pchip');

%plot(vx, vy, 'ko');
%display(vy);