#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>

#define pause system("pause > nul")    //�׳� ���� ���� ���� Ŀ�ǵ带 �ٿ��� ���̴�.
#define cls system("cls")    //�̰� ����

void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);
