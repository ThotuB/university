% truncated cone
rc1 = 2
rc2 = 1
h = 3

[xp,yp,z]=cylinder([rc1 rc2], 3);

zp=z*h;

surf(xp,yp,zp) 
hold on;

% pyramid
rp = 3
hp = 5

[xp,yp,z]=cylinder([rp 0], 6);

zp=h*z;

surf(xp,yp,zp) 
