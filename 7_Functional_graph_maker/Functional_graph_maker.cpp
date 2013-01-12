#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

//------------

typedef struct {
  double x;
  double y;
} Coord;

typedef double Func(double x);

typedef vector< vector<int> > CoordMap;

//------------
void printCoordMap(CoordMap&);
vector<Coord> genCoordSet(Func*,double,double,double);
int CoordSetToMap(vector<Coord>&,CoordMap&,int,int,double);
void genEmptyCoordMap(CoordMap&,int,int);

double f(double x){
  return pow(x,2);
}

//------------

int main(){
  vector<Coord> coordSet;
  CoordMap map;

  coordSet = genCoordSet(f,-10,10,0.5);
  CoordSetToMap(coordSet,map,40,40,0.2);
  printCoordMap(map);

  return 0;
}

//------------
void printCoordMap(CoordMap& map){
  cout<<"Graph:\n";
  for(int i=0;i<map.size();i++){
    for(int j=0;j<map[i].size();j++){
      cout<<(map[i][j] ? "*" : " ");
    }

    cout<<"\n";
  }
}

vector<Coord> genCoordSet(Func* f,double start,double end,double steplen){
  vector<Coord> CoordSet;
  Coord temp;

  CoordSet.reserve(20);

  for(double x=start;x<=end;x+=steplen){
    temp.x = x;
    temp.y = f(x);

    CoordSet.push_back(temp);
  }

  return CoordSet;
}

int CoordSetToMap(vector<Coord>& coordSet,CoordMap& map,int width,int height,double unitlen){
  genEmptyCoordMap(map,width,height);

  for(int i=0;i<coordSet.size();i++){
    int x,y;
    x = coordSet[i].x/unitlen + width/2; 
    y = coordSet[i].y/unitlen + height/2;

    if(x>map.size() || y>map[x].size()) continue;

    map[x][y] = 1;
  }

  return 1;
}

void genEmptyCoordMap(CoordMap& map,int width,int height){
  vector<int> column(height,0);
  for(int i=0;i<width;i++){
    map.push_back(column);
  }
}

