syms x y;

sol = solve( x^2 + y^2 - 4, x - y - 1, x, y);

for i=1:length(sol.x)
    disp([sol.x(i), sol.y(i)]);
end