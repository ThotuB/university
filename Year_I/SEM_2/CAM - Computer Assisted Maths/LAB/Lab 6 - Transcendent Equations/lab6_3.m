syms x a b p;

% i. a = 0; b = 0 => 0 = 0
% x -> R

f1 = eq_3(x,0,0,p);

% ii. a ~= 0; b = 0
% x = arcsin( sign(a)*p ) / 2

f2 = eq_3(x,a,0,p);
x2 = solve(f2, x);

% iii. a = 0; b ~= 0
% x = arccos( sign(b)*p - 2 ) / 2

f3 = eq_3(x,0,b,p);
x3 = solve(f3, x);

% iv. a ~= 0; b ~= 0

f = eq_3(x,a,b,p)

solu = solve(f)