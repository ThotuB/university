function [ rSol ] = lab5_2( Coef )
    rank = size(Coef) - 1;
    
    sol = roots(Coef);
    rSol = [];
    
    for i=1:rank(2)
        if imag(sol(i)) == 0
            rSol = [rSol; sol(i)];
        end
    end
end
