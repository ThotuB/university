coef = [1 7 3 4 4 5 7];
sol = roots(coef);

disp('real sols:');
for i=1:length(sol)
    if imag(sol(i)) == 0
        disp(sol(i));
    end
end