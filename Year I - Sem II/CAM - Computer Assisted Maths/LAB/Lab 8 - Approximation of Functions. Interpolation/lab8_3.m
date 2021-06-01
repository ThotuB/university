x = 0:1:6;

y = [15 30 75 60 60 40 55];

vx = 0:0.1:6;

[vy_linear, vy_cubic, vy_spline, vy_p2, vy_p5] = funct8_2n3( x, y, vx );

plot(x, y, 'ko');
hold on; grid;

%linear interpolation
plot(vx, vy_linear);

%cubic interpolation
plot(vx, vy_cubic);

%spline interpolation
plot(vx, vy_spline);

%parabolic regression
plot(vx, vy_p2);

%5th order polynomial regression
plot(vx, vy_p5);

legend('points', 'linear', 'cubic', 'spline', 'parabolic', '5th order polynomial');