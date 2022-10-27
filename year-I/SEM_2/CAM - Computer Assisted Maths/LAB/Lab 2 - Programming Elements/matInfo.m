function [transpM, rankM, detM] = matInfo( M )
  [row,col] = size(M);
  if ( row == col )
    transpM = M' ;
    rankM = rank(M) ;
    detM = det(M) ;
    
    display( transpM , rankM , detM);
  endif
endfunction