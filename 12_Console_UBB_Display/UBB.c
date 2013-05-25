#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<string.h>

#define MARKS_AMOUNT 2

typedef void AttrApply();

typedef struct {
  char mark[20];
  AttrApply* Call;
} UBBMark;

void PrintNextChar(char ch,UBBMark Marks[]);
int LookForMarks(char ch[],UBBMark Marks[]);
void LoadUbbMarks(UBBMark Marks[]);

void BMarkBg();
void BMarkEd();

/* ---------------- */

int main(int argc,char *argv[]){
  int row,col;
  FILE *fp;
  
  if(argc != 2){
    printf(" A Simple UBB Parser \n Usage: %s <UBB file name>\n",argv[0]);
    exit(1);
  }

  if((fp = fopen(argv[1],"r")) == NULL){
    perror("FAIL: Cannot open the file.\n");
    exit(1);
  }

  initscr();

  UBBMark Marks[MARKS_AMOUNT];
  LoadUbbMarks(Marks);
  getmaxyx(stdscr,row,col);

  int x,y;
  char ch;

  while((ch = fgetc(fp)) != EOF){
    PrintNextChar(ch,Marks);
    getyx(stdscr,y,x);

    if(y == (row - 1)){ /* If the curson is on the bottom of screen, display this. */
      mvprintw(row-1,0,"< Press Any Key >");
      refresh();
      getch();
      clear();
      move(0,0);
    }

  }

  fclose(fp);
  mvprintw(row-1,0,"< -- EOF -- >");
  refresh();
  getch();

  endwin();

  return 0;

}

void PrintNextChar(char ch,UBBMark Marks[]){
  static char buffer[20];
  static unsigned int bufLen = 0;

  buffer[bufLen] = ch;
  buffer[++bufLen] = '\0';
  short result = LookForMarks(buffer,Marks);
  switch(result){
    case -1:{
      printw("%s",buffer);
      buffer[0]='\0';
      bufLen = 0;
      break;
    }
    case -2:{
      break;
    }
    default:{
      if(result < MARKS_AMOUNT && result >= 0){
        Marks[result].Call();
        buffer[0]='\0';
        bufLen = 0;
        break;
      }
    }
  }

}

int LookForMarks(char ch[],UBBMark Marks[]){
  int i;
  for(i = 0;i<MARKS_AMOUNT;++i){
    int MarkLen = strlen(Marks[i].mark);
    int chLen = strlen(ch);

    if(strncmp(Marks[i].mark,ch,chLen) == 0){
      if(MarkLen == chLen){
        return i; /* Found one, return the Mark's offset. */
      }else if(MarkLen > chLen){
        return -2; /* Found one but not sure. */
      }
    }
  }

  return -1; /* Didn't find. */
}

void LoadUbbMarks(UBBMark Marks[]){
  strcpy(Marks[0].mark,"[b]");
  strcpy(Marks[1].mark,"[/b]");
  Marks[0].Call = &BMarkBg;
  Marks[1].Call = &BMarkEd;
}

void BMarkBg(){
  attron(A_BOLD);
}

void BMarkEd(){
  attroff(A_BOLD);
}
