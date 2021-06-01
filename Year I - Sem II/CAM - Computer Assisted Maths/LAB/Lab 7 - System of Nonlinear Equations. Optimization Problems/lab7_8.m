v0 = [1 0];

%options = optimset('LargeScale', 'off');
[vmin,fmin,exitflag,output] = fminunc('fvect8', v0);
% can reach minimum of -oo if x = 0 & y -> oo

fprintf('Minimum point [%g %g]\n',vmin);
fprintf('Minimum: %g\n',fmin);
fprintf('Optimization method: %s\n',output.algorithm);