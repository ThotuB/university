syms s;
alpha = 0.2;
KR = 1.2479;
HC = ( KR*(1 + 8*s) )/( 1 + 20*s );
HAT = ( 1 - 4*s )/( 1+2*s );
HGS = 1/( alpha + 7*s );

H0 = HC * HAT * HGS;

delta = (1+20*s)*(1+2*s)*(alpha + 7*s) + KR*(1+8*s)*(1-4*s);
delta = simplify(delta)