x = 0:1:6;

y = [15 30 75 60 60 40 55];

vx = [0.5 3.2 5.7];

[vy_linear, vy_cubic, vy_spline, vy_p2, vy_p5] = funct8_2n3( x, y, vx );

%linear interpolation
display(vy_linear);

%cubic interpolation
display(vy_cubic);

%spline interpolation
display(vy_spline);

%parabolic regression
display(vy_p2);

%parabolic regression
display(vy_p5);