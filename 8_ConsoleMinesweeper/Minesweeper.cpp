#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<ctime>

using std::cout;
using std::cin;
using std::vector;
using std::string;

typedef struct {
  int row;
  int col;

  int mines;
} MSGame;

typedef vector<string> MSRow;

typedef vector<MSRow> MSMap;

typedef struct {
  int x;
  int y;
} Coord;

//--------------------

int startGame(MSGame);
void printMap(MSMap&);
inline void printTag(string);
void generateMap(MSMap&,MSGame);
void generateEmptyMap(MSMap&,MSGame);
void generateMines(MSMap&,MSGame);
inline bool in_vector(vector<Coord>&,Coord);
void generateNumbers(MSMap&);
int getMinesAround(MSMap&,Coord);

//--------------------

int main(){
  MSGame game;

  srand(time(NULL));

  cout<<"Welcome to Minesweeper!\n\n"
    <<"Set map width:\n";
  cin>>game.col;
  cout<<"Set map height:\n";
  cin>>game.row;
  cout<<"Set mine numbers:\n";
  cin>>game.mines;

  startGame(game);

  return 0;
}

int startGame(MSGame game){
  MSMap map;

  generateMap(map,game);
  printMap(map);
}

void printMap(MSMap& map){
  cout<<"   ";
  for(int i=0;i<map.size();i++) cout<<i<<" ";
  cout<<"\n   ";
  for(int i=0;i<map.size();i++) cout<<"--";
  cout<<"\n";

  for(int i=0;i<map.size();i++){
    cout<<i<<"| ";

    for(int j=0;j<map[i].size();j++){
      printTag(map[i][j]);
    }

    cout<<"\n";
  }
}

void printTag(string tag){
  if(tag[0] == 'H') { cout<<"# "; return; } 
  else if(tag[0] == 'S') { cout<<"* "; return; }
  else if(tag[0] == 'D'){
    if(tag[1] == 'V') { cout<<"  "; return; }
    else if(tag[1] == 'X') {
      if(tag[2] == '0') { cout<<"* "; return; } 
      else if(tag[2] == '1') { cout<<"* "; return; } 
      else if(tag[2] == '2') { cout<<"& "; return; } 
    }else if(tag[1] == 'N'){
      cout<<tag[2]<<" ";
      return;
    }
  }else{
    cout<<"X ";
  }
  return;
}

void generateMap(MSMap& map,MSGame game){
  generateEmptyMap(map,game);
  generateMines(map,game);
  generateNumbers(map);

}

void generateEmptyMap(MSMap& map,MSGame game){
  MSRow row;

  for(int i=0;i<game.row;i++){
    for(int j=0;j<game.col;j++){
      row.push_back("HV-");
    }

    map.push_back(row);

    row.clear();
  }
}

void generateMines(MSMap& map,MSGame game){
  vector<Coord> minePosition(game.mines);
  Coord temp;

  for(int i=0;i<game.mines;i++){
    temp.x=rand()%game.col;
    temp.y=rand()%game.row;

    if(!in_vector(minePosition,temp)){ 
      minePosition.push_back(temp);
      map[temp.y][temp.x] = "DX0";
      //map[temp.y][temp.x] = "HX-";
    }
    else i--;
  }
  
}

void generateNumbers(MSMap& map){
  for(int i=0;i<map.size();i++){
    for(int j=0,mines=0;j<map[i].size();j++){
      Coord coord;
      coord.x = j;
      coord.y = i;

      if(map[i][j] == "HV-"){
        mines = getMinesAround(map,coord);
        if(mines) { map[i][j] = "DN"; map[i][j] += mines+48;} 
      }
    }
  }
}

int getMinesAround(MSMap& map ,Coord coord){
  vector<Coord> around;
  int count=0;

  for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++) {
      if(!i && !j) continue;

      Coord temp;
      temp.y = coord.y + i;
      temp.x = coord.x + j;

      if(temp.x >= 0 && temp.y >= 0 && temp.y < map.size() && temp.x < map[temp.y].size()) around.push_back(temp);
    }
  }

  for(int i=0;i<around.size();i++){
    int x = around[i].x,y = around[i].y;
//    if(map[y][x] == "HX-") count++;
    if(map[y][x] == "DX0") count++;
  }

  return count;
}

bool in_vector(vector<Coord>& my_vector,Coord element){
  for(int i=0;i<my_vector.size();i++){
    if(my_vector[i].x == element.x && my_vector[i].y == element.y) return true;
  }
  return false;
}

