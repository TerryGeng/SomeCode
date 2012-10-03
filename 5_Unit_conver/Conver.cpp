#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;


struct tagUnitConv {
  string ori;
  string des;
  double value;
};

typedef struct tagUnitConv UnitConv;

int load_units(const char* filename);
double units_conver(string ori,string des,double value);
double get_conver_value(string ori,string des);

vector<UnitConv> Units;

//--------------------

int main(){

  string ori,des;
  double input = 0;
  int loaded = load_units("Units.txt");

  cout<<"Units conver \n"
    <<"-------------\n"
    <<"Loaded: "<<loaded<<" Units.\n\n"
    <<"Original unit: ";
  cin>>ori;
  cout<<"\nObjective unit: ";
  cin>>des;
  cout<<"\nValue: ";
  cin>>input;

  if(!input) cout<<"You input a wrong number or zero.";
  else{
    double after = units_conver(ori,des,input);
    if(!after) cout<<"\nFailed.Have you add corresponding unit-info into Units Table yet? \n";
    else cout<<"\nResult: "<<after<<" "<<des<<"\n";
  }

  cin.ignore();

  return 0;

}


// Function: Load units to "Units".
// 
// @param char* filename  The localtion of Units Table.
// @return int  The number of units which loaded.
int load_units(const char* filename){
  fstream input;
  istringstream line;
  input.open(filename,fstream::in);

  UnitConv temp;

  Units.clear();
  for(string str;getline(input,str);){
    line.str(str);

    line>>temp.ori>>temp.des>>temp.value;
    Units.push_back(temp);

  }

  return Units.size();

}


// Function: Conver units.
//
// @param string ori  The original unit.
// @param string des  The objective unit.(destination)
// @param value  The value part.(E.g. The value of "100m" is 100.)
// @return double  The result.
double units_conver(string ori,string des,double value){
  double conver_tag = get_conver_value(ori,des);
  if(conver_tag == -1) return 0;

  return value * conver_tag;
}

// Function: Get corresponding unit tag from the Unit Table.
//
// @param string ori  The original unit.
// @param string des  The objective unit.
// @return double  The value which should times the original value.(E.g. 10m * 100 = 1000cm,In this case,the value is 100.)
double get_conver_value(string ori,string des){
  for(int i=0;i<Units.size();i++){
   if(Units[i].ori == ori && Units[i].des == des) return Units[i].value; 
  }

  return -1;
}
