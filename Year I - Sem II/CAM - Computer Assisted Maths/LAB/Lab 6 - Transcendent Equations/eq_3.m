function f = eq_3 ( x, a, b, p )
    f = 2 * b * (cos( x ))^2 + 2 * a * sin( x )* cos( x ) - p * sqrt( a^2 + b^2 ) + b;
    f = simplify(f);
end