r = 6371

[x,y,z]=sphere(360/15);

xc = r/2 * x
yc = r * y
zc = r * z

surf(xc,yc,zc)

axis('equal')