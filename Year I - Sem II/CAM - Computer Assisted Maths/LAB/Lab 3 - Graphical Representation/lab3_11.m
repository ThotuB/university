r = 5
h = 2

[x1, y1, z1] = cylinder( [2*r 0])

[x2, y2, z2] = cylinder( [0.5*r 2*r])

[x3, y3, z3] = cylinder( [r 0.5*r])

z11 = h * z1
z22 = h * z2
z33 = h * z3

surf(x1, y1, z11 + 2 * h)
hold on
surf(x2, y2, z22 + h)
hold on
surf(x3, y3, z33)