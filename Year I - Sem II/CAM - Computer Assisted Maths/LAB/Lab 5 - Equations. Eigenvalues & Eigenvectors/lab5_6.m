function [ minSV, maxSV, condNr] = lab5_6 ( A )
    [rowA, colA] = size(A);
    if rowA == colA
        sv = svd(A);
        
        minSV = sv(end);
        maxSV = sv(1);
        condNr = cond(A);
    else
        minSV = 0;
        maxSV = 0;
        condNr = 0;
        disp('Not a square matrix')
    end
end