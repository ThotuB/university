syms a b c;

sol = solve(a * c - b^2, a + c - 2*(b + 4), a * (c + 32) - (b + 4)^2, a, b, c);

for i=1:length(sol.a)
    disp([sol.a(i), sol.b(i), sol.c(i)])
end