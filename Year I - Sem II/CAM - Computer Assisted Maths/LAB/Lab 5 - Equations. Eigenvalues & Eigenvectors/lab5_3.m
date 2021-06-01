function [ cSol ] = lab5_3( Coef )
    rank = size(Coef) - 1;
    
    sol = roots(Coef);
    cSol = [];
    
    for i=1:rank(2)
        if abs(sol(i)) > 1
            cSol = [cSol; sol(i)];
        end
    end
end