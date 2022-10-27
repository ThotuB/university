function f = fvect9( v )
    x = v(1);
    y = v(2);
    z = v(3);
    
    f = x / ( x^2 + y^2 + z^2 + 1);
end