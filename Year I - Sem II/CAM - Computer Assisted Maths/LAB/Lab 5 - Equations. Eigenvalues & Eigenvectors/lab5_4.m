syms x n m;

f = x * (m - 1) - n/x + 1 - m;

Sol = solve(f, x);
x1 = Sol(1)
x2 = Sol(2)
