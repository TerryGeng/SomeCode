// A Functional graph drawing programme.
// 
// Can deal with many function(E.g. liner function...).
//
// I'm working on adding float support.So I create a new branch.
//
// This programme hasn'n completed yet.I will complete this programme and merge this branch into the master in a few days.
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
};

typedef struct CoordTag Coord;
typedef struct RangeTag Range;

typedef double Func(double x);

typedef map<double,bool> Column;
typedef map<double,Column> CoordMap;

//------------
void printCoordMap(CoordMap&);

vector<Coord> genCoordSet(Func*,Range range,double steplen=1);

void CoordSetToCoordMap(vector<Coord>& coordSet,CoordMap& map,Range range,double unitlen=1);

void getEmptyCoordMap(CoordMap& map,Range range,double unitlen=1);

double unitePrecision(double value,double precision);

double f(double x){
  return x;
}

//------------

int main(){
  vector<Coord> coordSet;
  CoordMap map;
  Range range;

  range.xRangeStart=6;
  range.xRangeEnd=-6;
  range.yRangeStart=6;
  range.yRangeEnd=-6;

  coordSet = genCoordSet(f,range,1);
  CoordSetToCoordMap(coordSet,map,range,2);
  printCoordMap(map);

  return 0;
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

  for(double x=range.xRangeEnd;x<=range.xRangeStart;x+=steplen){
    temp.x = x;
    temp.y = f(x);

    if(temp.y>range.yRangeStart || temp.y<range.yRangeEnd) continue;

    CoordSet.push_back(temp);
  }

  return CoordSet;
}

void CoordSetToCoordMap(vector<Coord>& coordSet,CoordMap& map,Range range,double unitlen){
  getEmptyCoordMap(map,range,unitlen);

  for(int i=0;i<coordSet.size();i++){
    map[unitePrecision(coordSet[i].y,unitlen)][coordSet[i].x] = 1;
  }
}

void getEmptyCoordMap(CoordMap& map,Range range,double unitlen){
  Column temp;
  for(double x=range.xRangeEnd;x<=range.xRangeStart;x+=unitlen){
    temp[x] = 0;
  }
  for(double y=range.yRangeEnd;y<=range.yRangeStart;y+=unitlen){
    map[y] = temp;
  }

}

double unitePrecision(double value,double precision){
  double sign=1;

  if(value < 0) sign = -1;

  double sum=0,temp=0;

  value = fabs(value);

  while((temp = sum + precision) < value){
    sum = temp;
  }

  if((value - sum) > precision/2){
    sum += precision;
  }

  sum *= sign;

  return sum;
}
