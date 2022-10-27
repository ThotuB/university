A1 = [2 -3 0;-6 8 -1;0 3 4];
b1 = [7; -5; 1];

cond1 = rcond(A1)

if cond1 > 0.2
    disp('System 1 is well-conditioned');
else
    disp('System 1 is ill-conditioned');
end

A2 = [190 7; 2 200];
b2 = [4; -2];

cond2 = rcond(A2)

if cond2 > 0.2
    disp('System 2 is well-conditioned');
else
    disp('System 2 is ill-conditioned');
end