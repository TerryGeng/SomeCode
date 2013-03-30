#include<stdio.h>

#define MAX_LENGTH 100

int main(){

  int mchar;
  char buffer[MAX_LENGTH + 100];

  int length=0,bufferlen=0;

  for( ; (mchar = getchar())!=EOF ; length++){
    if(mchar == ' '){
      if(length>=MAX_LENGTH){
        putchar('\n');
        length = bufferlen;
      }else{
        printf(buffer);
        bufferlen = 0;
      }
    }else if(bufferlen == MAX_LENGTH){
      printf(buffer);
      putchar('\n');
      bufferlen = 0;
      length = 0;
    }

    buffer[bufferlen] = mchar;
    buffer[++bufferlen] = '\0';
  }

  return 0;
}


