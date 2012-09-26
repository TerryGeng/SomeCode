#include<isostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;


struct UnitConv {
  string convF;
  string convT;
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

  fstream input;
  istringstream line;

  input.open(filename,fatream::in);

  for(istringstream line,Units temp;line.str(input.getline());){

    line>>temp.convF>>temp.convT>>temp.ex;

    Units.push_back(temp);

  }

  return Units.size();

}
