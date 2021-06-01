%plot3(x, y, z)

[x,y] = meshgrid(-3:0.1:3)
z =  x.^3  - 3 .* x .* y.^2

%subplot(3,1,1), mesh(x, y, z)
subplot(3,1,2), surf(x, y, z)
subplot(3,1,3), surfl(x, y, z)

grid on;