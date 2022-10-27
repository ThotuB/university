function g = systNonLin1 ( v )
    x = v(1);
    y = v(2);
    
    g(1) = sin(x + y) - 1.1 * x - 0.2;
    g(2) = 1.1 * x^2 + 2 * y^2 - 1;
end