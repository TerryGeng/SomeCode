// Look up a string in some text. 
//
// Like the "instr" in Visual Basic.

#include<cstdio>
#include<cstring>

int instr(char*,char*);
//--------------------

int main(){
  
  char str[100],obj[100];

  printf("Please input a sentence.(less than 100 letters) \n");
  scanf("%s",str);
  printf("Please input the objective parts. \n");
  scanf("%s",obj);

  int position;

  if((position = instr(str,obj)) == -1) printf("Cannot find. \n");
  else printf("Found.The position of objective is %i. \n",position);

  return 0;
}


// Function: Look up a string in the text.
//
// @param char* str Original string.
// @param char* obj Objective string(what you are looking for).
// @return int The position of objective string first appeard. If couldn't find, return -1.

int instr(char* str,char* obj){
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
