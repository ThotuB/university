v0 = [0.6 -0.2 -0.1];

[vmin,fmin,exitflag,output] = fminsearch('fvect9', v0);

fprintf('Minimum point [%f %f %f]\n',vmin);
fprintf('Minimum: %g\n',fmin);
fprintf('Optimization method: %s\n',output.algorithm);