A = [-6 8 -1; 2 -3 0];
b = [-5; 7];

disp('The system is compatible and undetermined')
z = sym('z');

Areduced = A(:, [1 2]);
breduced = [-5 + z; 7];

Sreduced = inv(Areduced) * breduced;
x = Sreduced(1)
y = Sreduced(2)