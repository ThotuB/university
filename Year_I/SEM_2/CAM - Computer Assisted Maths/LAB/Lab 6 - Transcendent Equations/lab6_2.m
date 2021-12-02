lim = 10*pi;
x = -lim:0.05:lim;

f = exp( cos( x ));
g = sin( x ) + 1;

plot(x, f, 'b', x, g,'r--');
axis([-lim lim -0.5 3]);
disp('The equation has an inf number of solutions, because its periodic');

[x0, y0] = ginput(2)

sol1 = fzero('eqTrans2', x0(1));
sol2 = fzero('eqTrans2', x0(2));

display(sol1);
display(sol2);

