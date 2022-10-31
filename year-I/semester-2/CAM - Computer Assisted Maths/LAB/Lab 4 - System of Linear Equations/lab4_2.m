A1 = [4 3 -1; -1 1 1; 1 0 3; 4 4 3];
b1 = [2; 0; -1; 1];

rankA1 = rank(A1)
%rankA1b1 = rank([A1 b1])

if rank(A1) == rank([A1 b1])
    X1 = pinv(A1) * b1
else
    disp('The system is not compatible.')
end

A2 = [-6 8 -1; 2 -3 0];
b2 = [-5; 7];

rankA2 = rank(A2)
%rankA2b2 = rank([A2 b2])

if rank(A2) == rank([A2 b2])
    X2 = pinv(A2) * b2
else
    disp('The system is not compatible.')
end