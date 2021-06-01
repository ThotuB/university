function [vy_linear, vy_cubic, vy_spline, vy_p2, vy_p5] = funct8_2n3 ( x, y, vx )
    %linear interpolation
    vy_linear = interp1(x, y, vx, 'linear');

    %cubic interpolation
    vy_cubic = interp1(x, y, vx, 'pchip');

    %spline interpolation
    vy_spline = interp1(x, y, vx, 'spline');

    %parabolic regression
    P2 = polyfit(x, y, 2);

    vy_p2 = polyval(P2, vx);

    %parabolic regression
    P5 = polyfit(x, y, 5);

    vy_p5 = polyval(P5, vx);
end