A = zeros(3,3,4);
A(:,:,4) = [1, 1, 3;
     1, 5, 1;
     3, 1, 1];
 
c = zeros(1,4);
B = zeros(3, 3, 3);

% STEP I
% 1
c(1) = 1;
% 2
B(:,:,1) = A(:,:,4);
c(2) = -trace(B(:,:,1));

for k=2:1:3
   B(:,:,k) = A(:,:,4)*(B(:,:,k-1) + c(k)*eye(3));
   c(k+1) = -(1/k)*trace(B(:,:,k));
end

display(A(:,:,4));
display(B);
display(c);

% STEP II
sol = roots(c)


% STEP III
for lam=1:3
    A(:,:,lam)= A(:,:,4);
    for i=1:3
        A(i,i,lam) = A(i,i,4) - sol(4-lam);
    end
end

A1 = A(2:3,2:3,1)
b1 = -A(2:3,1,1)
x1 = [1;A1\b1]

A2 = A(1:2:3,2:3,2)
b2 = -A(1:2:3,1,2)
x2 = [1;A2\b2]

A3 = A(1:2,2:3,3)
b3 = -A(1:2,1,3)
x3 = [1;A3\b3]