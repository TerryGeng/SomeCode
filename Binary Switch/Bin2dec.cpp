#include<cstdio>
#include<cmath>
#include<fstream>
#include<cstring>

using namespace std;

double Bin_to_Dec(char* orginal,int size);

//----------------------

int main(){
  fstream input;
  fstream output;
  char row[3000]; 

  input.open("input.txt",fstream::in);
  output.open("output.txt",fstream::out);

  for(; input.getline(row,3000) && strcmp(row,"-1") != 0;){
    output<<Bin_to_Dec(row,strlen(row))<<"\n";
  }

  input.close();
  output.close();

  return 0;
}


double Bin_to_Dec(char* orginal,int size){
  double temp = 0;

  for(int i = 0;i<size;++i){
    temp += (*(orginal + size - i - 1) - 48) * pow(2,i);
  }

  return temp;
}
