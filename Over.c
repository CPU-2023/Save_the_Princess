#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>


//Ű���尪
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

//�Լ� ���� 
void OverDraw();   //���� ���
void init1();        //�ܼ�â ũ���Լ� 
int Overmenu();     //�޴� ���&���� �Լ� 
int O_keyControl();   //ȭ��ǥ �����ϴ� ��


//main�Լ� 
int Over()
{
    init1();
    OverDraw();
    Overmenu();
    return 0;
}
//�ܼ� ȭ�� ���� �Լ� 
void init1() {
    system("mode con:cols=120 lines=30 | title Save the Princess");
}

//���� ��� �Լ�  \n");
void OverDraw()
{
    int x = 5, y = 3;

    gotoxy(x, y++); printf("\t\t     _______  _______  __   __  _______         _______  __   __  _______  ______      __ ");
    gotoxy(x, y++); printf("\t\t    |       ||   _   ||  |_|  ||       |       |       ||  | |  ||       ||    _ |    |  |");
    gotoxy(x, y++); printf("\t\t    |    ___||  |_|  ||       ||    ___|       |   _   ||  |_|  ||    ___||   | ||    |  |");
    gotoxy(x, y++); printf("\t\t    |   | __ |       ||       ||   |___        |  | |  ||       ||   |___ |   |_||_   |  |");
    gotoxy(x, y++); printf("\t\t    |   ||  ||       ||       ||    ___|       |  |_|  ||       ||    ___||    __  |  |__|");
    gotoxy(x, y++); printf("\t\t    |   |_| ||   _   || ||_|| ||   |___        |_______|  |___|  |_______||___|  |_|  |__|");
    gotoxy(x, y++); printf("\t\t    |_______||__| |__||_|   |_||_______|                                                  ");
    gotoxy(x, y++);
    gotoxy(x, y++);
    gotoxy(x, y++);
    gotoxy(x, y++); printf("\t       $$$$$$$$$$$                    |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|                 ");
    gotoxy(x, y++); printf("\t     $$$$$$$$$$$$$$$                  |     ___       ___       ___     |                 ");
    gotoxy(x, y++); printf("\t   $$$$$$$$$$$$$$$$$$$                |    |   |     |   |     |   |    |                 ");
    gotoxy(x, y++); printf("\t   $$   $  $$$$$  $ $$                |   |     |   |     |   |     |   |                 ");
    gotoxy(x, y++); printf("\t   $$ $    $$$$$ $  $$                -----------------------------------                 ");
    gotoxy(x, y++); printf("\t    $$$$$$$$$$$$$$$$$       |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|   ");
    gotoxy(x, y++); printf("\t     $$$$$$$$$$$$$$$        |     ____       ____       ____     ____       ____      |   ");
    gotoxy(x, y++); printf("\t      $$$$      $$$         |    |    |     |    |     |    |   |    |     |    |     |   ");
    gotoxy(x, y++); printf("\t       $$$      $$          |   |      |   |      |   |      | |      |   |      |    |   ");
    gotoxy(x, y++); printf("\t        $$$$$$$$$$          -----------------------------------------------------------   ");
}

//�޴� ��� �Լ� & �޴� ���ñ�� �Լ�
int Overmenu() {
    int x = 55;
    int y = 26;
    int menuIndex = 0;
    char menuItems[3][20] = { "���ư���","��    ��" };

    while (1) {
        // �޴� ������ ���
        for (int i = 0; i < 2; i++) {
            gotoxy(x, y + i);
            if (i == menuIndex) printf("> %s", menuItems[i]);
            else printf("  %s", menuItems[i]);
        }

        // �Է� ó��
        int n = O_keyControl();
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
                return main();
            }
            else if (menuIndex == 1) {
                exit(0);

            }
        }
        }
    }
}


////��,�Ʒ� ,��,�� Ű�� ���� �Լ� 
int O_keyControl() {
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