#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>

#define pause system("pause > nul")    //그냥 내가 많이 쓰는 커맨드를 줄여준 것이다.
#define cls system("cls")    //이것 또한

void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);
