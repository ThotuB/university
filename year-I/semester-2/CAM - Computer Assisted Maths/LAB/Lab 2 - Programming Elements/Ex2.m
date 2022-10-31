v1=[2 3 1 9 2 -1 -3 5];
v2=[2 3 1 9 2 1 3 5];

v1=v2;

[v1_len]=size(v1);
p=1;

for i=1:v1_len(2);
  if ( v1(i) < 0 )
    break;
  endif
  p=p*v1(i);
endfor

display(p);