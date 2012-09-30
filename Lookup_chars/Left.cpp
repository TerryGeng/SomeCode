#include<cstdio>
#include<cstring>

int left(char*,char*);
//--------------------

int main(){
  
  char str[100],obj[100];

  printf("Please input a sentence.(less than 100 letters) \n");
  scanf("%s",str);
  printf("Please input the objective parts. \n");
  scanf("%s",obj);

  int position;

  if((position = left(str,obj)) == -1) printf("Cannot find. \n");
  else printf("Found.The position of objective is %i. \n",position);

  return 0;
}

int left(char* str,char* obj){
 int lengthS,lengthO;

 lengthS = strlen(str);
 lengthO = strlen(obj);

 for (int i = 0;i<=lengthS-lengthO;i++){

   for(int j = 0;j<lengthO;j++){

     if(str[i+j] == obj[j]){
       if(j == lengthO - 1) return i;
       continue;
     }else{
       break;
     }
   }
 }

 return -1;

}
