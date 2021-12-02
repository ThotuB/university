function [ X ] = lab4_3 ( A, b )
    [~, colA] = size(A);
    if rank(A) == rank([A b])
        if rank(A) == colA
            X = pinv(A) * b;
        else
            X = 0;
            disp('The system is undetermined')
        end
    else
        X = 0;
        disp('The system is not compatible.')
    end
end