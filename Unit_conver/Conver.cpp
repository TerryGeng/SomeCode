#include<isostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;


struct UnitConv {
  string ConvF;
  string ConvT;
  int ex;
}

int load_units(string filename);

vector<UnitConv> Units;

//--------------------

int main(){

  load_units("Units.txt");

  return 0;

}


// Load units to "Units".
// 
// @return val:The number of units which loaded.
int load_units(string filename){

  UnitConv temp;

  temp.ConvF = "m"; 
  temp.ConvT = "m";
  temp.ex = 0;

  Units.push_back(temp);

  return Units.size();

}
