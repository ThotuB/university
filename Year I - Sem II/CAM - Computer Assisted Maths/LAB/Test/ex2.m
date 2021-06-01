i = sqrt(-1);

disp('f(0) = ');
disp(func2(0));
disp('f(-1) = ');
disp(func2(-1));
disp('f(3+2i) = ');
disp(func2(3+2*i));
disp('f(2) = ');
disp(func2(2));

plot(-1, func2(-1), 'xb', 2, func2(2), 'xb');
grid on;