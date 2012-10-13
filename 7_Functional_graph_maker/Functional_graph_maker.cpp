// A Functional graph drawing programme.
// 
// Can deal with many function(E.g. liner function...).
// If you compile and run this programme now,it will output the graph of y=x^2.
// But now,It can't do well with float.I will repair this problem in a few days(In fact,you can edit the function "f" to change the function you want draw).
//
// This programme used many STL containers(E.g. vector,map),I didn't do any performance optimizations.
//
// This programme hasn'n completed yet.I will complete this programme and add some comments in a few days.
//
//-----------

#include<iostream>
#include<cmath>
#include<vector>
#include<map>

using namespace std;

//------------

struct CoordTag {
  double x;
  double y;
};

struct RangeTag{
  double xRangeStart;
  double xRangeEnd;
  double yRangeStart;
  double yRangeEnd;
  int graphH;
  int graphW;
};

typedef struct CoordTag Coord;
typedef struct RangeTag Range;

typedef double Func(double x);

typedef map<double,bool> Column;
typedef map<double,Column> CoordMap;

//------------
double f(double);
void printCoordMap(CoordMap&);
vector<Coord> genCoordSet(Func*,Range range,double steplen=1);
void CoordSetToCoordMap(vector<Coord>& coordSet,CoordMap& map,Range range,double unitlen=1);
void getZeroCoordMap(CoordMap& map,Range range,double unitlen=1);

//------------

int main(){
  vector<Coord> coordSet;
  CoordMap map;
  Range range;

  range.xRangeStart=-30;
  range.xRangeEnd=30;
  range.yRangeStart=30;
  range.yRangeEnd=-30;
  range.graphH=60;
  range.graphW=60;

  coordSet = genCoordSet(f,range);
  CoordSetToCoordMap(coordSet,map,range);
  printCoordMap(map);

  return 0;
}

double f(double x){
  return pow(x,2);
}

//------------
void printCoordMap(CoordMap& map){
  for(CoordMap::iterator it=(--map.end());it!=(--map.begin());it--){
    Column& col = (*it).second;
    for(Column::iterator cIt=col.begin();cIt!=col.end();cIt++){
      cout<<((*cIt).second ? "*" : " ");
    }

    cout<<"\n";
  }
}

vector<Coord> genCoordSet(Func* f,Range range,double steplen){
  vector<Coord> CoordSet;
  Coord temp;

  CoordSet.reserve(20);

  for(double x=range.xRangeStart;x<=range.xRangeEnd;x+=steplen){
    temp.x = x;
    temp.y = f(x);

    if(temp.y>range.yRangeStart || temp.y<range.yRangeEnd) continue;

    CoordSet.push_back(temp);
  }

  return CoordSet;
}

void CoordSetToCoordMap(vector<Coord>& coordSet,CoordMap& map,Range range,double unitlen){
  getZeroCoordMap(map,range,unitlen);

  for(int i=0;i<coordSet.size();i+=unitlen){
    if(fabs(coordSet[i].x) > range.graphW/2 || fabs(coordSet[i].y) > range.graphH/2) continue;

    map[coordSet[i].y][coordSet[i].x] = 1;
  }
}

void getZeroCoordMap(CoordMap& map,Range range,double unitlen){
  Column temp;
  for(double x=-(range.graphW/2);x<=range.graphW/2;x++){
    temp[x] = 0;
  }
  for(double y=-(range.graphH/2);y<=range.graphH/2;y++){
    map[y] = temp;
  }

}

