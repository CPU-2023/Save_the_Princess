#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include "console.h"

//Ű���尪
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

//�Լ� ���� 
void TitleDraw();   //���� ���
void init();        //�ܼ�â ũ���Լ� 
//oid printGameInstructions(); // ���� ��� ȭ�� ��� �Լ�
int menuDraw();     //�޴� ���&���� �Լ� 
int keyControl();   //ȭ��ǥ �����ϴ� ��


//main�Լ� 
int main()
{
    init();
    TitleDraw();
    menuDraw();
    Function();
    escreen();


    //printGameInstructions(); // ���� ��� ȭ�� ��� �Լ�
    //while (1) {
    //    TitleDraw(); //ȭ�� ���
    //    int menuCode = menuDraw();
    //    if (menuCode == 0) {
    //        //���� �������� �̵�
    //    }
    //    else if (menuCode == 2) {
    //        //���� ������ �̵�
    //        infoDraw();
    //    }
    //    else if (menuCode == 4){
    //        return 0;
    //    }
    //    system("cls");
    //}
    return 0;
}
//�ܼ� ȭ�� ���� �Լ� 
void init() {
    system("mode con:cols=120 lines=30 | title Save the Princess");
}

//���� ��� �Լ�  \n");
void TitleDraw()
{
    int x = 5, y = 3;
    textcolor(14);

    gotoxy(x, y++); printf("\t    _______  _______  __   __  _______      _______  ______    ___   __    _  _______  _______  _______ ");
    gotoxy(x, y++); printf("\t   |       ||   _   ||  | |  ||       |    |       ||    _ |  |   | |  |  | ||       ||       ||       |");
    gotoxy(x, y++); printf("\t   |  _____||  |_|  ||  |_|  ||    ___|    |    _  ||   | ||  |   | |   |_| ||       ||    ___||  _____|");
    gotoxy(x, y++); printf("\t   | |_____ |       ||       ||   |___     |   |_| ||   |_||_ |   | |       ||       ||   |___ | |_____ ");
    gotoxy(x, y++); printf("\t   |_____  ||       ||       ||    ___|    |    ___||    __  ||   | |  _    ||      _||    ___||_____  |");
    gotoxy(x, y++); printf("\t    _____| ||   _   | |     | |   |___     |   |    |   |  | ||   | | | |   ||     |_ |   |___  _____| |");
    gotoxy(x, y++); printf("\t   |_______||__| |__|  |___|  |_______|    |___|    |___|  |_||___| |_|  |__||_______||_______||_______|");
    gotoxy(x, y++);
    gotoxy(x, y++);
    gotoxy(x, y++);
    gotoxy(x, y++); printf("\t        $$$$$$$ \t                                |��                                ");
    gotoxy(x, y++); printf("\t       $$ $$$$$$\t   $$                           |                                  ");
    gotoxy(x, y++); printf("\t       $$$$$$$$$\t  $$$$         -----------------------------------                 ");
    gotoxy(x, y++); printf("\t$      $$$      \t   $$          |     ___       ___       ___     |                 ");
    gotoxy(x, y++); printf("\t$$     $$$$$$$  \t               |    |   |     |   |     |   |    |                $$");
    gotoxy(x, y++); printf("\t$$$   $$$$$     \t               |   |     |   |     |   |     |   |               $$$$");
    gotoxy(x, y++); printf("\t $$  $$$$$$$$$$ \t               -----------------------------------                $$");
    gotoxy(x, y++); printf("\t $$$$$$$$$$$    \t   |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|    ");
    gotoxy(x, y++); printf("\t  $$$$$$$$$$    \t   |     ____       ____       ____     ____       ____      |    ");
    gotoxy(x, y++); printf("\t    $$$$$$$$    \t   |    |    |     |    |     |    |   |    |     |    |     |    ");
    gotoxy(x, y++); printf("\t     $$$$$$     \t   |   |      |   |      |   |      | |      |   |      |    |    ");
    gotoxy(x, y++); printf("\t\t                   -----------------------------------------------------------    ");
}

//�޴� ��� �Լ� & �޴� ���ñ�� �Լ�
int menuDraw() {
    int x = 55;
    int y = 26;
    int menuIndex = 0;
    char menuItems[3][20] = { "�� �� �� ��", "�� �� �� ��", "    �� ��    " };

    while (1) {
        // �޴� ������ ���
        for (int i = 0; i < 3; i++) {
            gotoxy(x, y + i);
            if (i == menuIndex) printf("> %s", menuItems[i]);
            else printf("  %s", menuItems[i]);
        }

        // �Է� ó��
        int n = keyControl();
        switch (n) {
        case UP: {
            if (menuIndex > 0) menuIndex--;
            break;
        }
        case DOWN: {
            if (menuIndex < 2) menuIndex++;
            break;
        }
        case SUBMIT: {
            if (menuIndex == 0) {
                return Function();
            }
            else if (menuIndex == 1) {
                GameRule();

            }
            else if (menuIndex == 2) {
                exit(0);
            }
        }
        }
    }
}


////��,�Ʒ� ,��,�� Ű�� ���� �Լ� 
int keyControl() {
    int temp = _getch();

    // �̼��� ��ġ ������ ���� �߰� �ڵ�
    if (temp == 0xE0 || temp == 0)
    {
        temp = _getch();
    }

    switch (temp) {
    case 72: // VK_UP
        return UP;
    case 80: // VK_DOWN
        return DOWN;
    case 75: // VK_LEFT
        return LEFT;
    case 77: // VK_RIGHT
        return RIGHT;
    case 13: // Space
        return SUBMIT;
    default:
        return 0;
    }
}