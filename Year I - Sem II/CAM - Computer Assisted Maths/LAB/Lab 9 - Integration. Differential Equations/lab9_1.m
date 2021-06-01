for i=1:1:11
    x(i) = -1.1 + 0.1 * i;
    y(i) = ( i * x(i)^2 )/( x(i) - 1 ) - 2/(i + 1);
end

I = trapz(x, y);

display(I);