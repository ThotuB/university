A = [1 -1; 3 2];

[vec, val] = eig(A);

for i=1:2
    disp('Value: ');
    disp(val(i,i));
    for j=1:3
        disp('   - Vector:')
        disp(j * vec(:,i))
    end
end