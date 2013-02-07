#include<stdio.h>

bool isDivChar(char c);
void printA(int* array,int along);

int main(){

  int wlong[20]={0};
  bool in=0;
  int slong=0;
  
  for(int c = getchar();c != EOF;c = getchar()){
    if(isDivChar(c)){
      if(slong !=0){
        ++wlong[slong];
        slong=0;
      }
    }else
      ++slong;
  }
  if(slong != 0) ++wlong[slong];
  
  printA(wlong,sizeof(wlong));

  return 0;
}

bool isDivChar(char c){

  if(c == ' '||c == '\n'||c == '\t'|| \
      c == ','||c == '.'||c == ';' || \
      c == '(' || c == ')' || c == '{' || \
      c == '}') return true;
  return false;
}

void printA(int* array,int along){
  for(int i=0;i<along/sizeof(int);i++){
    printf("%2d:",i);
    for(int j=0;j<array[i];j++){
      putchar('-');
    }
    printf("(%d)\n",array[i]);
  }

}
