coefA = [2 -3 0 3 -10 -8];

disp('The solutions are:')

Xa = roots(coefA);
xa1 = X(1)
xa2 = X(2)
xa3 = X(3)
xa4 = X(4)
xa5 = X(5)

% sqrt(1 - x^2) = x^2 + x + 1
% x^4 + 2*x^3 + 4*x^2 + 2*x = 0
% -1 <= x <= 1

coefB = [1 2 4 2 0];

Xb = roots(coefB);

for i=1:4
    if imag(Xb(i)) == 0 && Xb(i) >= -1 && Xb(i) <= 1
        disp(Xb(i));
    end
end

