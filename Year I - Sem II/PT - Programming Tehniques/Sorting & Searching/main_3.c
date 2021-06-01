#include <stdio.h>
#include <stdlib.h>

int big_guess(int begin, int end,int cnt){
  int mid=(begin+end)/2;
  char ans[3];

  if (end - begin == 1){
    if (cnt%2==0){
      printf("Is the number lower than %d? [Y/N]",end);
    }
    else{
      printf("Is the number greater than %d? [Y/N]",begin);
    }

    ans[0]=getchar();   // this should be enter(\n)
    ans[1]=getchar();

    if (cnt%2==0){
      if ( ans[1] == 'y' || ans[1] == 'Y'){
        return begin;
      }
      else if ( ans[1] == 'n' || ans[1] == 'N'){
        return end;
      }
    }
    else {
      if ( ans[1] == 'y' || ans[1] == 'Y'){
        return end;
      }
      else if ( ans[1] == 'n' || ans[1] == 'N'){
        return begin;
      }
    }
  }


  if (cnt%2==0){
    printf("Is the number lower than %d? [Y/N]",mid);
  }
  else{
    printf("Is the number greater than %d? [Y/N]",mid);
  }

  ans[0]=getchar();   // this should be enter(\n)
  ans[1]=getchar();


  if (cnt%2==0){
    if ( ans[1] == 'y' || ans[1] == 'Y'){
      return big_guess(begin,mid,cnt+1);
    }
    else if ( ans[1] == 'n' || ans[1] == 'N'){
      return big_guess(mid,end,cnt+1);
    }
  }
  else {
    if ( ans[1] == 'y' || ans[1] == 'Y'){
      return big_guess(mid,end,cnt+1);
    }
    else if ( ans[1] == 'n' || ans[1] == 'N'){
      return big_guess(begin,mid,cnt+1);
    }
  }

}

int big_guess(int begin, int end,int cnt){
  int mid=(begin+end)/2;
  char ans[3];

  if (end - begin == 1){
    if (cnt%2==0){
      printf("Is the number lower than %d? [Y/N]",end);
    }
    else{
      printf("Is the number greater than %d? [Y/N]",begin);
    }

    ans[0]=getchar();   // this should be enter(\n)
    ans[1]=getchar();

    if (cnt%2==0){
      if ( ans[1] == 'y' || ans[1] == 'Y'){
        return begin;
      }
      else if ( ans[1] == 'n' || ans[1] == 'N'){
        return end;
      }
    }
    else {
      if ( ans[1] == 'y' || ans[1] == 'Y'){
        return end;
      }
      else if ( ans[1] == 'n' || ans[1] == 'N'){
        return begin;
      }
    }
  }


  if (cnt%2==0){
    printf("Is the number lower than %d? [Y/N]",mid);
  }
  else{
    printf("Is the number greater than %d? [Y/N]",mid);
  }

  ans[0]=getchar();   // this should be enter(\n)
  ans[1]=getchar();


  if (cnt%2==0){
    if ( ans[1] == 'y' || ans[1] == 'Y'){
      return big_guess(begin,mid,cnt+1);
    }
    else if ( ans[1] == 'n' || ans[1] == 'N'){
      return big_guess(mid,end,cnt+1);
    }
  }
  else {
    if ( ans[1] == 'y' || ans[1] == 'Y'){
      return big_guess(mid,end,cnt+1);
    }
    else if ( ans[1] == 'n' || ans[1] == 'N'){
      return big_guess(begin,mid,cnt+1);
    }
  }

}

int main(){
  char c;

  printf("Did you pick a number between 1 and 100? [Y/N]");
  c=getchar();
  switch (c){
    case 'y':
    case 'Y':
      printf("Your number is: %d",big_guess(1,100,0));
      break;
    case 'n':
    case 'N':
      printf("Ok...");
      break;
  }

  return 0;
}
