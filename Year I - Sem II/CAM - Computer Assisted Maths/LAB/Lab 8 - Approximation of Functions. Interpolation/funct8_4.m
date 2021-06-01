function [vy_linear, vy_p3] = funct8_4 ( x, y, vx )
    %linear interpolation
    vy_linear = interp1(x, y, vx, 'linear');
    
    %cubic regression
    P3 = polyfit(x, y, 3);

    vy_p3 = polyval(P3, vx);
end