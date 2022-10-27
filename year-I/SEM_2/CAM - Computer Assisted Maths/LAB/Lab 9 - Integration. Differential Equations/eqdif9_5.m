function dq = eqdif9_5 ( t, q )
    dq = zeros(6,1);

    g = 10;
    m1 = 10;
    m2 = 4.15;
    m3 = 0.5;
    J3 = 0.015;

    F1 = -58.6 .* sin(2.*t)
    F2 = 23.25 .* exp(-t) .* ( sin(4.*t) - 3.*cos(4.*t)) + 45.601
    M3 = 0.004 .* t.^2
    
    dq(1) = q(2);
    dq(3) = q(4);
    dq(5) = q(6);
    
    dq(2) = F1./(m1 + m2 + m3)
    dq(4) = (F2 - m2*g - m3*g)./(m2 + m3)
    dq(6) = M3 ./ J3;
    
end