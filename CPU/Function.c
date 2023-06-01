#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>

#pragma warning (disable : 4996)

//esc �ƽ�Ű �ڵ�
#define ESC 27
//�ִ� �� ��
#define MAXENEMY 30
//�ִ� �Ѿ� ��
#define MAXBALL 10

//����
int Score;
struct Player {
    int x, y;
};

//�� ����ü
struct Enemy
{
    BOOL exist;
    //���� ����
    int Type;
    int x, y;
    //���� �¿�� ������ �� ����ϴ� ����
    int movementcal;

    //���� ������ �ִϸ��̼��� ǥ���ϱ� ���� ����
    int nFrame;
    int nStay;
}
Enemy[MAXENEMY];


struct Bullet
{
    BOOL exist;
    int x, y;
    int nFrame;
    int nStay;
}
Bullet[MAXBALL];

const char* Type_Enemy[] = { " ^_^ ", " >_< ", " *_* ", " x_x " };

void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void drawscreen() {
    textcolor(14);
    printf("���������������������������������������\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("��                                                                        ��\n");
    printf("���������������������������������������\n");
}
void Function()
{

    int ch;
    int i, j;
    BOOL BulletFound;


    srand((unsigned)time(NULL));
    system("cls");
    //CursorView(0);//Ŀ�� �����

    struct Player player;
    player.x = 60;
    player.y = 60;

    struct Bullet bullet;
    bullet.x = -1;
    bullet.y = 0;
    Score = 0;
    drawscreen();

    while (1) {

        // �¿� �̵� ó��
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (player.x > 6)
                player.x--;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (player.x < 72)
                player.x++;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            if (player.y > 6)
                player.y--;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            if (player.y < 72)
                player.y++;
        }

        // Ű �Է� ó��-- �Ѿ˹߻�� ����(���ݴ� �ڵ� �м�����)
        if (kbhit())
        {
            ch = getch();
            if (ch == 0xE0 || ch == 0)
            {
                getch();
            }
            else
            {
                switch (ch)
                {
                case ' ': // Space
                    if (bullet.x == -1)
                    {
                        bullet.x = player.x;
                        bullet.y = 23;
                    }
                    break;
                case ESC:
                    goto end;
                }
            }
        }

        // �Ʊ� �Ѿ� �̵� �� ���
        if (bullet.x != -1)
        {
            gotoxy(bullet.x, bullet.y);
            putch('  ');
            bullet.y--;
            if (bullet.y <= 2) { // y ��ǥ�� 0 ������ �� �Ѿ� ����
                gotoxy(bullet.x, bullet.y);
                putch(' ');
                bullet.x = -1;
                bullet.y = -1;
            }
            else {
                gotoxy(bullet.x, bullet.y);
                putch('i');
            }
        }

        // ���� ����
        if (rand() % 50 == 0)
        {
            for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++) { ; }
            if (i != MAXENEMY)
            {
                if ((rand() % 2) + 1 == 1)
                {
                    Enemy[i].x = 7;
                    Enemy[i].movementcal = 1;
                }

                else
                {
                    Enemy[i].x = 70;
                    Enemy[i].movementcal = -1;
                }

                //while�� �ٲ���!
                for (;;) {
                    Enemy[i].y = rand() % 10 + 2;
                    for (BulletFound = FALSE, j = 0; j < MAXENEMY; j++)
                    {
                        if (Enemy[j].exist == TRUE && Enemy[j].y == Enemy[i].y)
                        {
                            BulletFound = TRUE;
                            break;
                        }
                    }
                    if (BulletFound == FALSE)
                    {
                        break;
                    }
                }
                Enemy[i].nFrame = Enemy[i].nStay = rand() % 6 + 1;
                Enemy[i].Type = rand() % (sizeof(Type_Enemy) / sizeof(Type_Enemy[0])); //random(sizeof(Type_Enemy) / sizeof(Type_Enemy[0]));
                Enemy[i].exist = TRUE;
            }
        }


        // ������ �Ʊ� �Ѿ��� �浹 ����
        for (i = 0; i < MAXENEMY; i++)
        {
            if (Enemy[i].x == 120) Enemy[i].exist = FALSE;

            if (Enemy[i].exist == FALSE)
                continue;

            if (Enemy[i].y == bullet.y && abs(Enemy[i].x - bullet.x) <= 2)
            {
                gotoxy(bullet.x, bullet.y); putch(' ');
                bullet.x = -1;
                Enemy[i].exist = FALSE;
                gotoxy(Enemy[i].x - 3, Enemy[i].y);
                puts("       ");
                Score += 5;
                if (Score == 20) Success();
                break;

            }

        }

        // ���� �Ѿ� �̵�
        for (i = 0; i < MAXBALL; i++)
        {
            if (Bullet[i].exist == FALSE)
                continue;

            if (--Bullet[i].nStay == 0)
            {
                Bullet[i].nStay = Bullet[i].nFrame;
                gotoxy(Bullet[i].x, Bullet[i].y); putch(' ');

                if (Bullet[i].y >= 23)
                {
                    Bullet[i].exist = FALSE;
                }
                else
                {
                    Bullet[i].y++;
                    gotoxy(Bullet[i].x, Bullet[i].y); putch('��');
                }
            }

        }

        // ���� �Ѿ˰� �Ʊ��� �浹 ����
        for (i = 0; i < MAXBALL; i++) {
            if (Bullet[i].exist == FALSE) continue;
            if (Bullet[i].y == 23 && abs(Bullet[i].x - player.x) <= 2) {
                gotoxy(player.x - 3, 21); puts("   .   ");
                gotoxy(player.x - 3, 22); puts(" .  . .");
                gotoxy(player.x - 3, 23); puts("..:V:..");
                Sleep(1000);

                goto end;
            }
        }

        // ���� �̵� �� ���
        for (i = 0; i < MAXENEMY; i++) {
            if (Enemy[i].exist == FALSE) continue;
            if (--Enemy[i].nStay == 0) {
                Enemy[i].nStay = Enemy[i].nFrame;
                if (Enemy[i].x >= 69 || Enemy[i].x <= 6) {
                    Enemy[i].exist = FALSE;
                    gotoxy(Enemy[i].x - 3, Enemy[i].y);
                    puts("       ");
                }
                else
                {
                    Enemy[i].x += Enemy[i].movementcal;
                    gotoxy(Enemy[i].x - 3, Enemy[i].y);
                    puts(Type_Enemy[Enemy[i].Type]);
                    // �Ѿ� �߻�
                    if (rand() % 20 == 0) {
                        for (j = 0; j < MAXBALL && Bullet[j].exist == TRUE; j++) { ; }
                        if (j != MAXBALL) {
                            Bullet[j].x = Enemy[i].x + 2;
                            Bullet[j].y = Enemy[i].y + 1;
                            Bullet[j].nFrame = Bullet[j].nStay = Enemy[i].nFrame * 6;
                            Bullet[j].exist = TRUE;
                        }
                    }
                }
            }
        }



        // ������ �� ���� ���
        CursorView(0);
        gotoxy(player.x - 3, 23);
        puts(" �� ");
        gotoxy(67, 2);
        printf("����: %d", Score);

        gotoxy(80, 10);
        printf("�������� ���ָ� ���Ͽ���!��");

        gotoxy(80, 12);
        printf("�� : ��");

        gotoxy(80, 14);
        printf("�Ʒ� : ��");

        gotoxy(80, 16);
        printf("���� : ��");

        gotoxy(80, 18);
        printf("������ : ��");

        gotoxy(80, 20);
        printf("���� : SPACE");

        // �ʴ� 10 ������
        Sleep(40);
    }
end:
    /*system("cls");
    gotoxy(30, 10);
    printf("==========================GAMEOVER==========================\n\n");
    gotoxy(58, 15);
    printf("����=%d\n\n\n\n\n\n\n\n\n\n\n\n", Score);
    CursorView(0);
    getchar();*/
    textcolor(15);
    Over();

}