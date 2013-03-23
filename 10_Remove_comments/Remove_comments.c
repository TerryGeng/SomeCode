#include<stdio.h>

int main(){
  char mChar = 0;

  int print = 1;

  int lSlash = 0;
  int lAst = 0;

  while((mChar = getchar()) != EOF){
    if(print == 1){
      if(mChar == '/' && lSlash == 0){
        lSlash = 1;
        continue;
      }else if(lSlash == 1){
        if(mChar == '*'){
          lSlash = 0;
          print = 0;
          continue;
        }else putchar('/');
        lSlash = 0;
      }
      putchar(mChar);
    }else{
      if(mChar == '*' && lAst == 0){
        lAst = 1;
        continue;
      }else if(lAst == 1){
        if(mChar == '/') print = 1;
        else lAst = 0;
      }
    }
  }

  return 0;
}
