kE = 1000;
kp = 500; Tp = 60;
kc = 125; Tc = 300;

A = [-1/Tp      1/Tp;
     kp/(kc*Tc) -(1+kp/kc)/Tc];
B = [kE/(kp*Tp) 0;
     0          1/Tc];
C = [1 0;
     0 1];
D = [0 0;
     0 0];