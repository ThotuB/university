function [lastLine, secondLine, prod, minElem] = funct2( M )
    [rows, cols] = size(M);
    
    if rows >= 8 & cols >= 10
        lastLine = M(end,:);
        secondLine = M(2,:);
        prod = lastLine .* secondLine;
        minElem = lastLine(1);
        for i=2:length(lastLine)
            if lastLine(i) < minElem
                minElem = lastLine(i);
            end
        end
    else
        disp('Invalid matrix - size to small');
        lastLine = [];
        secondLine = [];
    end
end