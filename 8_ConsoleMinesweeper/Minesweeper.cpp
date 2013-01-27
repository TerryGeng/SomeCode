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

typedef struct {
  char status;
  char type;
  int attribute;
} MSTag;

typedef vector<MSTag> MSRow;

typedef vector<MSRow> MSMap;

typedef struct {
  int x;
  int y;
} Coord;

//--------------------

int startGame(MSGame);
void printMap(MSMap&,bool all=0);
void printTag(MSTag);
inline void printAllTag(MSTag);
void generateMap(MSMap&,MSGame);
void generateEmptyMap(MSMap&,MSGame);
void generateMines(MSMap&,MSGame);
inline bool in_vector(vector<Coord>&,Coord);
void generateNumbers(MSMap&);
int getMinesAround(MSMap&,Coord);
int executeInput(MSMap&,string,MSGame);
int touchBlock(MSMap&,Coord);
vector<Coord> getBlocksAround(MSMap&,Coord);
bool inMapRange(Coord,MSGame);
int markBlock(MSMap&,Coord);
int unmarkBlock(MSMap&,Coord);
bool checkWin(MSMap&,MSGame);

//--------------------

int main(){
  MSGame game;

  srand(time(NULL));

  cout<<"\033[2J";

  cout<<"\033[32mWelcome to Minesweeper\033[0m\n\n"
    <<"Set map width:\n";
  cin>>game.col;
  cout<<"Set map height:\n";
  cin>>game.row;
  cout<<"Set mine numbers:\n";
  cin>>game.mines;


  startGame(game);

  cin.ignore(1);

  return 0;
}

int startGame(MSGame game){
  MSMap map;

  cout<<"GameStart!\n";
  cin.ignore(1);

  generateMap(map,game);

  while(1){
    if(checkWin(map,game)){
      cout<<"\n---You Win!---\n";
      printMap(map,1);
      break;
    }
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
      printMap(map,1);
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
    else if(first == "p" || first == "m" || first == "r"){
      Coord coord;
      int x=0,y=0;

      if(!(sin>>x)) return 4;
      if(!(sin>>y)) return 4;

      coord.x = x;
      coord.y = y;

      if(!inMapRange(coord,game)) return 4;

      if(first == "p"){
        int result = touchBlock(map,coord);

        if(result == 1) return 1;
        else if(result == 2) return 2;
        else if(result == 0) return 4;

      }else if(first == "m"){
        markBlock(map,coord);
        return 1;
      }else if(first == "r"){
        unmarkBlock(map,coord);
        return 1;
      }
    }
  }

  return 4;
}

bool inMapRange(Coord coord,MSGame game){
  if(coord.x >= game.col || coord.y >= game.row) return 0;
  return 1;
}

bool checkWin(MSMap& map,MSGame game){
  int selected = 0;

  for(int y = 0;y<game.row;y++){
    for(int x = 0;x<game.col;x++){
      if(map[y][x].status == 'S'){
        if(map[y][x].type == 'X')
          selected++;
        else return 0;
      }
    }
  }

  if(selected == game.mines) return 1;
  return 0;
  
}

int touchBlock(MSMap& map,Coord coord){
  MSTag &tag = map[coord.y][coord.x];
  if(tag.status == 'H' && tag.type == 'V'){
    tag.status = 'D';

    vector<Coord> around;
    around = getBlocksAround(map,coord);

    for(int i=0;i<around.size();i++){
      MSTag &stag = map[around[i].y][around[i].x];
      if(stag.status == 'H' && (stag.type == 'V'  || stag.type == 'N')) {
        touchBlock(map,around[i]);
      }
    }
    return 1;
  }else if(tag.status == 'H' && tag.type == 'N'){
    tag.status = 'D';
    return 1;
  }else if(tag.status == 'H' && tag.type == 'X'){
    tag.status = 'D';
    tag.attribute = 1;
    return 2;
  }
  return 0;
}

int markBlock(MSMap& map,Coord coord){
  MSTag &tag = map[coord.y][coord.x];
  tag.status = 'S';
  return 1;
}

int unmarkBlock(MSMap& map,Coord coord){
  MSTag &tag = map[coord.y][coord.x];
  tag.status = 'H';
  return 1;
}

void printMap(MSMap& map,bool all){
  cout<<"\033[32m   ";
  for(int i=0;i<map.size();i++) cout<<i<<" ";
  cout<<"\n   ";
  for(int i=0;i<map.size();i++) cout<<"--";
  cout<<"\033[0m\n";

  for(int i=0;i<map.size();i++){
    cout<<"\033[32m"<<i<<"| \033[0m";

    for(int j=0;j<map[i].size();j++){
      if(all) printAllTag(map[i][j]);
      else printTag(map[i][j]);
    }

    cout<<"\n";
  }
}

void printAllTag(MSTag tag){
  if(tag.status == 'S'){
    if(tag.type == 'X') { cout<<"* "; return; } 
    else { cout<<"& "; return; }
  }else if(tag.type == 'V') { 
    cout<<"  "; 
    return; 

  }else if(tag.type == 'X') {
    if(tag.attribute == 0) { cout<<"* "; return; } 
    else if(tag.attribute == 1) { cout<<"X "; return; } 
  }else if(tag.type == 'N'){
    cout<<tag.attribute<<" ";
    return;
  }
  return;
}

void printTag(MSTag tag){
  if(tag.status == 'H') { cout<<"# "; return; } 
  else if(tag.status == 'S') { cout<<"@ "; return; }
  else if(tag.status == 'D'){
    if(tag.type == 'V') { cout<<"  "; return; }
    else if(tag.type == 'X') {
      if(tag.attribute == 0) { cout<<"* "; return; } 
      else if(tag.attribute == 1) { cout<<"* "; return; } 
      else if(tag.attribute == 2) { cout<<"& "; return; } 
    }else if(tag.type == 'N'){
      cout<<tag.attribute<<" ";
      return;
    }
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
  MSTag tag;
  tag.status = 'H';
  tag.type = 'V';
  tag.attribute = 0;

  for(int i=0;i<game.row;i++){
    for(int j=0;j<game.col;j++){
      row.push_back(tag);
    }

    map.push_back(row);

    row.clear();
  }
}

void generateMines(MSMap& map,MSGame game){
  vector<Coord> minePosition(game.mines);
  Coord temp;
  MSTag tag;

  tag.status = 'H';
  //tag.status = 'D';
  tag.type = 'X';
  tag.attribute = 0;

  for(int i=0;i<game.mines;i++){
    temp.x=rand()%game.col;
    temp.y=rand()%game.row;

    if(!in_vector(minePosition,temp)){ 
      minePosition.push_back(temp);
      map[temp.y][temp.x] = tag;
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

      if(map[i][j].status == 'H' && map[i][j].type == 'V'){
        mines = getMinesAround(map,coord);
        if(mines) { 
          map[i][j].type = 'N';
          map[i][j].status = 'H';
          map[i][j].attribute += mines;
        } 
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
    if(map[y][x].type == 'X') count++;
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

