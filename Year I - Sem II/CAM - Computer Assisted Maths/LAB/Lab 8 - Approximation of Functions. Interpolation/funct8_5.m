function funct8_5 ( x, y )
    vx = min(x):0.1:max(x);

    %piecewise cubic
    vy_cubic = interp1(x, y, vx, 'pchip');
    
    %spline cubic
    vy_spline = interp1(x, y, vx, 'spline');
    
    %graphing
    plot(x, y, 'ko', vx, vy_cubic, vx, vy_spline);
    grid;
    legend('points', 'cubic', 'spline');
end