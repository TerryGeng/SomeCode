#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;


struct tagUnitConv {
  string convF;
  string convT;
  int ex;
};

typedef struct tagUnitConv UnitConv;

int load_units(const char* filename);

vector<UnitConv> Units;

//--------------------

int main(){

  string convF,convT;
  double input = 0;

  load_units("Units.txt");

  cout<<"Please type-in the number. \n\n"
    <<"x * 10 ^ y \n"
    <<"x : \n";

  cin>>input;


  cin.ignore();

  return 0;

}


// Load units to "Units".
// 
// @return val:The number of units which loaded.
int load_units(const char* filename){

  fstream input;
  istringstream line;

  input.open(filename,fstream::in);

  UnitConv temp;
  for(string str;getline(input,str);){

    line.str(str);

    Units.clear();

    line>>temp.convF>>temp.convT>>temp.ex;

    Units.push_back(temp);

  }

  return Units.size();

}
