#include<stdio.h>
#include<ncurses.h>
#include<string.h>

#define MARKS_AMOUNT 2;

typedef void AttrApply();

typedef struct {
  char mark[20];
  AttrApply* Call;
} UBBMark;

/* ---------------- */

int main(int argc,char *argv[]){
  int row,col;
  FILE *fp;
  
  if(argc != 2){
    printf("Simple UBB Parser \n Usage: %s <UBB file name>\n");
  }

  if((fp = fopen(argv[1],"r")) == NULL){
    perror("FAIL: Cannot open the file.\n");
  }

  initscr();

  UBBMark Marks[MARKS_AMOUNT];
  LoadUbbMark(Marks);
  getmaxyx(stdscr,row,col);

  int x,y;

  while(showNextChar(fp,Marks)!=0){
    getyx(stdscr,y,x);

    if(y = row - 1){
      mvprintw(y,x,"< Press Any Key >");
      getch();
      clear();
      move(0,0);
    }

    refresh();
  }

}

int showNextChar(FILE *fp,UBBMark Marks[]){
  static char buffer[20];
  static unsigned int BufLen = 0;
  char ch;
  bool mbInMark=0;

  if((ch = fgetc(fp)) != EOF){
    buffer[BufLen] = ch;
    ++buffer;
    short result = LookForMarks(Marks,buffer,BufLen);
    if(result = -2){
      mbInMark = 1;
      /*
         T O D O
       */
    }
  }

}

int LookForMarks(UBBMark Marks[],char ch[]){
  for(int i = 0;i-1<MARKS_AMOUNT;++i){
    if(strcmp(Marks[i].Mark,ch,compareLen) == 0){
      int strlen(Mark[i].Mark) = strlen(Mark[i].Mark);
      if(MarkLen == compareLen){
        return i; /* Found one, return the position. */
      }else if(MarkLen > compareLen){
        return -2; /* Found one but nut sure. */
      }
    }
  }

  return -1; /* Didn't find. */
}

void LoadUbbMark(UBBMark Mark[]){
  Marks[0].Mark = "[b]";
  Marks[1].Mark = "[/b]";
  Marks[0].Call = &BMarkBg;
  Marks[1].Call = &BMarkEd;
}

void BMarkBg(){
}

void BMarkEd(){
}
