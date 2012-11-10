#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<ctime>
#include<sstream>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::istringstream;

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
int executeInput(MSMap&,string,MSGame);
int touchBlock(MSMap&,Coord);
vector<Coord> getBlocksAround(MSMap&,Coord);

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

  cout<<"GameStart!\n";

  generateMap(map,game);

  while(1){
    string input;

    printMap(map);
    cout<<"\nInput> ";
    std::getline(cin,input);

    int result = executeInput(map,input,game);
    if(result == 1){
      continue;
    }
    else if(result == 2){
      cout<<"\n---Game over!---\n";
      printMap(map);
      break;
    }else if(result == 3){
      break;
    }else if(result == 4){
      cout<<"\nWrong input!\n";
        continue;
    }

    cout<<"\n------------------------\n\n";
  }
}

int executeInput(MSMap& map,string input,MSGame game){
  istringstream sin(input);
  string first;

  if(sin>>first){
    if(first == "q") return 3;
    else if(first == "p"){
      Coord coord;
      int x=0,y=0;

      if(!(sin>>x)) return 4;
      if(!(sin>>y)) return 4;

      cout<<x<<" "<<y<<"\n";
      if(x >= game.col || y >= game.row) return 4;

      coord.x = x;
      coord.y = y;

      int result = touchBlock(map,coord);

      if(result == 1) return 1;
      else if(result == 2) return 2;
      else if(result == 0) return 4;
    }else if(first == "m"){
      Coord coord;

      if(!(sin>>coord.x || sin>>coord.y) || (coord.x >= game.col || coord.y >= game.row)) return 4;
      //if(markBlock(map,coord) == 1) return 1;
    }
  }

  return 4;
}

int touchBlock(MSMap& map,Coord coord){
  string &tag = map[coord.y][coord.x];
  if(tag == "HV-"){
    tag = "DV-";

    vector<Coord> around;
    around = getBlocksAround(map,coord);

    for(int i=0;i<around.size();i++){
      string &stag = map[around[i].y][around[i].x];
      if(stag == "HV-") {
        stag = "DV-";
        touchBlock(map,around[i]);
      }else if(stag.substr(0,2) == "HN") {
        stag[0] = 'D';
      }
    }
    return 1;
  }else if(tag.substr(0,2) == "HN"){
    tag[0] = 'D';
    return 1;
  }else if(tag == "HX-"){
    tag = "DX1";
    return 2;
  }
  return 0;
}

int markBlock(MSMap& map,Coord coord){
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
    cout<<"X "<<tag;
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
      //map[temp.y][temp.x] = "DX0";
      map[temp.y][temp.x] = "HX-";
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
        //if(mines) { map[i][j] = "DN"; map[i][j] += mines+48;} 
        if(mines) { map[i][j] = "HN"; map[i][j] += mines+48;} 
      }
    }
  }
}

int getMinesAround(MSMap& map ,Coord coord){
  vector<Coord> around;
  int count=0;

  around = getBlocksAround(map,coord);

  for(int i=0;i<around.size();i++){
    int x = around[i].x,y = around[i].y;
    if(map[y][x] == "HX-") count++;
    //if(map[y][x] == "DX0") count++;
  }

  return count;
}

vector<Coord> getBlocksAround(MSMap& map,Coord coord){
  vector<Coord> around;
  for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++) {
      if(!i && !j) continue;

      Coord temp;
      temp.y = coord.y + i;
      temp.x = coord.x + j;

      if(temp.x >= 0 && temp.y >= 0 && temp.y < map.size() && temp.x < map[temp.y].size()) around.push_back(temp);
    }
  }

  return around;
}

bool in_vector(vector<Coord>& my_vector,Coord element){
  for(int i=0;i<my_vector.size();i++){
    if(my_vector[i].x == element.x && my_vector[i].y == element.y) return true;
  }
  return false;
}

