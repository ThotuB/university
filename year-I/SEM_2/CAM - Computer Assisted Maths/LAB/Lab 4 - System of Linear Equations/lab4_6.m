function lab4_6 ( A, b )
    [~, colA] = size(A);
    
    disp('The system is:')
    
    if rank(A) == rank([A b])
        if rank(A) == colA
            disp('i) compatible & determined')
        else
            disp('ii) compatible & undetermined')
        end
    else
        disp('iii) incompatible')
    end
end