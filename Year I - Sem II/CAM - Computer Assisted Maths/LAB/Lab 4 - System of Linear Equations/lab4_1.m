A = [4 3 -1; -1 1 1; 1 0 3];
b = [2; 0; -1];

if rank(A)==rank([A b]) 
    if det(A) ~= 0
        X = inv(A) * b
    else
        disp('The system is unetermined')
    end
else
    disp('The system is not compatible.')
end