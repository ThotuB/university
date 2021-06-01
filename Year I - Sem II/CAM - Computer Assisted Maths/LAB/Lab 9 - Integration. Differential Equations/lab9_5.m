q0 =[1; 2; 1; -1; -0.5; 0];
interv = [0, 3];

[tval, qval] = ode113('eqdif9_5', interv, q0)

% plot in 2d
% plot(tval, qval(:, 1:2:5));
% legend('q1', 'q2', 'q3');

% plot in 3d
plot3(qval(:,1), qval(:,2), qval(:,3));
grid on;
