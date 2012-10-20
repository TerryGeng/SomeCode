// A Functional graph drawing programme.
// 
// The graph is formed of chars;
//
// Can deal with many function(E.g. liner function...).
//
// This programme used a lot of STL containers.Such as map,vector.But maybe it's not a good idea to use a double as the key of a map,especially use a negative double,it can cause some 
// strange problem such as you have already added a key,but you can't use find() to find the key. At very first,I tried to use map to store the coordinates.Later,It proved that I was 
// wrong.I have to add a number to each coordnate to keep them positive.Since map can't work well,I considered that I should use vector instead of map,but I'm not patient enough to keep
// maintaining it.
//
// If you want to change the function you want to draw,just change the function f.
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
  double steplen;
};

typedef struct CoordTag Coord;
typedef struct RangeTag Range;

typedef double Func(double x);

typedef map<double,bool> Column;
typedef map<double,Column> CoordMap;

//------------
void printCoordMap(CoordMap&);

vector<Coord> genCoordSet(Func*,Range range);

void CoordSetToCoordMap(vector<Coord>& coordSet,CoordMap& map,Range range);

void getEmptyCoordMap(CoordMap& map,Range range,double unitlen);

double unitePrecision(double value,double precision);

double f(double x){
  return 1/x+5;
}

//------------

int main(){
  vector<Coord> coordSet;
  CoordMap map;
  Range range;

  range.xRangeStart=10;
  range.xRangeEnd=-10;
  range.yRangeStart=10;
  range.yRangeEnd=0;
  range.steplen=0.1;

  coordSet = genCoordSet(f,range);
  CoordSetToCoordMap(coordSet,map,range);
  printCoordMap(map);

  return 0;
}

//------------
void printCoordMap(CoordMap& map){
  cout<<"Graph:\n";
  for(CoordMap::iterator it=(--map.end());it!=(--map.begin());it--){
    cout.precision(5);
    //cout<<fixed<<(*it).first<<" ";
    Column& col = (*it).second;
    for(Column::iterator cIt=col.begin();cIt!=col.end();cIt++){
      cout<<((*cIt).second ? "*" : " ");
    }

    cout<<"\n";
  }
}

vector<Coord> genCoordSet(Func* f,Range range){
  vector<Coord> CoordSet;
  Coord temp;

  CoordSet.reserve(20);

  for(double x=range.xRangeEnd;x<=range.xRangeStart;x+=range.steplen){
    temp.x = x;
    temp.y = f(x);

    if(temp.y>range.yRangeStart || temp.y<range.yRangeEnd) continue;

    temp.x=fabs(temp.x-range.xRangeEnd);
    temp.y=fabs(temp.y-range.yRangeEnd);

    CoordSet.push_back(temp);
  }

  return CoordSet;
}

void CoordSetToCoordMap(vector<Coord>& coordSet,CoordMap& map,Range range){
  getEmptyCoordMap(map,range,range.steplen);
  //cout<<"CoordSetToCoordMap:"<<coordSet.size()<<"\n";

  double tempY = 0;

  for(int i=0;i<coordSet.size();i++){
    tempY = unitePrecision(coordSet[i].y,range.steplen);

    if(map.find(tempY) != map.end()){
      map[tempY][coordSet[i].x] = 1;
      //cout<<"O Y "<<tempY<<" X "<<coordSet[i].x<<" "<<"\n";
    }else{
      //cout<<"N Y "<<tempY<<" X "<<coordSet[i].x<<" "<<"\n";
    }
  }
}

void getEmptyCoordMap(CoordMap& map,Range range,double unitlen){
  //cout<<"getEmptyCoordMap:\n";
  Column temp;
  for(double x=0;x<=fabs(range.xRangeStart-range.xRangeEnd);x+=unitlen){
    temp[x] = 0;
  }
  for(double y=0;y<=fabs(range.yRangeStart-range.yRangeEnd);y+=unitlen){
    //cout<<"Y "<<y<<"\n";
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
  double half = precision/2;
  if(((value - sum) - half) >= -0.0000001){
    sum += precision;
  }

  sum *= sign;

  return sum;
}
