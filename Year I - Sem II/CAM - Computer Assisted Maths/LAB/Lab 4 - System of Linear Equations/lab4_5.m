a = sym('a');
b = sym('b');
c = sym('c');

A = [a -b 1; -c 1 b; 1 c -a];
B = [c; a; b];

d = det(A);
factor(d);

disp('The system is compatible and determined')

Sol = inv(A) * B