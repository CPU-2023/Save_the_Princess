#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>

#pragma warning (disable : 4996)

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

//esc �ƽ�Ű �ڵ�
#define ESC 27
//�ִ� �� ��
#define MAXENEMY 4
//�ִ� �Ѿ� ��
#define MAXBALL 10

void SuccessDraw();   //���� ���
void init2();        //�ܼ�â ũ���Լ� 
int Successmenu();     //�޴� ���&���� �Լ� 
int S_keyControl();   //ȭ��ǥ �����ϴ� ��

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
    int Frame;
    int Stay;
}
Enemy[MAXENEMY];


struct Bullet
{
    BOOL exist;
    int x, y;
    int Frame;
    int Stay;
}
Bullet[MAXBALL];

const char* Type_Enemy[] = { " �¢¢� ", " ��__�� ", " ��o�� ", " ������ " };

void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void drawscreen() {
    textcolor(14);
    printf("��������������������������������������� ������������������������������������������������������������������������\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��                                                                        �� ��                                  ��\n");
    printf("��������������������������������������� ������������������������������������������������������������������������\n");
}

void escreen()
{
    srand((unsigned int)time(NULL)); // ���� �ʱ�ȭ

    // �� �ʱ�ȭ
    for (int i = 0; i < MAXENEMY; i++)
    {
        Enemy[i].exist = FALSE;
        Enemy[i].Frame = 0;
        Enemy[i].Stay = 0;
        Enemy[i].x = rand() % 80 + 10; // 10���� 89������ ������ x ��ǥ
        Enemy[i].y = rand() % 20 + 1;  // 1���� 20������ ������ y ��ǥ
    }
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
        int available = -1;
        for (int i = 0; i < MAXENEMY; i++) {
            if (Enemy[i].exist == FALSE) {
                available = i;
                break;
            }
        }

        if (available != -1) {
            int position = 0;
            int newX, newY;

            do {
                position = 0;
                if ((rand() % 2) + 1 == 1) {
                    newX = 7;
                    Enemy[available].movementcal = 1;
                }
                else {
                    newX = 70;
                    Enemy[available].movementcal = -1;
                }
                newY = rand() % 10 + 2;

                for (int j = 0; j < MAXENEMY; j++) {
                    if (Enemy[j].exist && (Enemy[j].x == newX && Enemy[j].y == newY)) {
                        position = 1;
                        break;
                    }
                }
            } while (position);

            Enemy[available].x = newX;
            Enemy[available].y = newY;
            Enemy[available].Frame = Enemy[available].Stay = rand() % 6 + 1;
            Enemy[available].Type = rand() % (sizeof(Type_Enemy) / sizeof(Type_Enemy[0]));
            Enemy[available].exist = TRUE;
        }


        // ������ �Ʊ� �Ѿ��� �浹 ����
        for (i = 0; i < MAXENEMY; i++)
        {
            if (Enemy[i].x > 120 || Enemy[i].y <= 2) Enemy[i].exist = FALSE;

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
                if (Score == 50) Success();
                break;

            }

        }

        // ���� �Ѿ� �̵�
        for (i = 0; i < MAXBALL; i++)
        {
            if (Bullet[i].exist == FALSE)
                continue;

            if (--Bullet[i].Stay == 0)
            {
                Bullet[i].Stay = Bullet[i].Frame;
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
            if (--Enemy[i].Stay == 0) {
                Enemy[i].Stay = Enemy[i].Frame;
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
                            Bullet[j].Frame = Bullet[j].Stay = Enemy[i].Frame * 6;
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

        gotoxy(82, 4);
        printf("��������! ���ָ� ���Ͽ���~��");

        gotoxy(80, 7);
        printf("=============�̼�!===============\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t���� �����Ͽ� ���ָ� ���ѳ���!");

        gotoxy(80, 11);
        printf("�ش�Ű�� ����Ͽ� ���� �����϶�!");

        printf("\n");

        gotoxy(80, 15);
        printf("\t\t������ : ��");

        gotoxy(80, 17);
        printf("\t\t����   : �� \n");

        gotoxy(80, 19);
        printf("\t\t����   : SPACE\n\n");

        // �ʴ� 10 ������
        Sleep(40);
    }
end:
    textcolor(15);
    Over();

}
//main�Լ� 
int Success()
{
    init2();
    SuccessDraw();
    Successmenu();
    return 0;
}
//�ܼ� ȭ�� ���� �Լ� 
void init2() {
    system("mode con:cols=120 lines=30 | title Save the Princess");
}

//���� ��� �Լ�  \n");
void SuccessDraw()
{
    int x = 5, y = 1;
    textcolor(14);
    gotoxy(x, y++); printf("\t\t\t\t  __   __  ___   _______  _______  ___   _______  __    _");
    gotoxy(x, y++); printf("\t\t\t\t |  |_|  ||   | |       ||       ||   | |       ||  |  | |");
    gotoxy(x, y++); printf("\t\t\t\t |       ||   | |  _____ || _____||   | |   _   ||   |_| |");
    gotoxy(x, y++); printf("\t\t\t\t |       ||   | | |_____ | |_____ |   | |  | |  ||       |");
    gotoxy(x, y++); printf("\t\t\t\t |       ||   | |_____ || _____  ||   | |  |_|  ||  _    |");
    gotoxy(x, y++); printf("\t\t\t\t | ||_|| ||   |  _____| | _____| ||   | |       || | |   |");
    gotoxy(x, y++); printf("\t\t\t\t |_|   |_||___| |_______||_______||___| |_______||_|  |__|");
    gotoxy(x, y++); printf("\t\t\t\t _______  __   __  _______  _______  _______  _______  _______");
    gotoxy(x, y++); printf("\t\t\t\t|       ||  | |  ||       ||       ||       ||       ||       |");
    gotoxy(x, y++); printf("\t\t\t\t|  _____||  | |  ||       ||       ||    ___||  _____||  _____|");
    gotoxy(x, y++); printf("\t\t\t\t| |_____ |  |_|  ||       ||       ||   |___ | |_____ | |_____ ");
    gotoxy(x, y++); printf("\t\t\t\t| _____ ||       ||      _||      _||   _____|| _____|| ____  |");
    gotoxy(x, y++); printf("\t\t\t\t  _____|||       ||     |_ |     |_ |   |___  _____| | _____| |");
    gotoxy(x, y++); printf("\t\t\t\t|_______||_______||_______||_______||_______||_______||_______|");
    gotoxy(x, y++);
    gotoxy(x, y++); printf("                                          \t\t\t|�� ");
    gotoxy(x, y++); printf("                                          \t\t\t| ");
    gotoxy(x, y++); printf("\t   $$$    $$$     \t\t      ������������������                ");
    gotoxy(x, y++); printf("\t  $$$$$  $$$$$    \t\t      ��                              ��                ");
    gotoxy(x, y++); printf("\t $$$$$$$$$$$$$$$  \t\t      ��       ��   �� : %d           ��               ", Score);
    gotoxy(x, y++); printf("\t$$$$$$$$$$$$$$$$$ \t\t      ��                              ��                ");
    gotoxy(x, y++); printf("\t $$$$$$$$$$$$$$   \t\t      ������������������                ");
    gotoxy(x, y++); printf("\t  $$$$$$$$$$$     \t  |-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-| ");
    gotoxy(x, y++); printf("\t    $$$$$$$       \t  |     ____       ____       ____     ____       ____      | ");
    gotoxy(x, y++); printf("\t      $$$$        \t  |    |    |     |    |     |    |   |    |     |    |     | ");
    gotoxy(x, y++); printf("\t       $$         \t  |    |    |     |    |     |    |   |    |     |    |     | ");
    gotoxy(x, y++); printf("\t                \t    ----------------------------------------------------------- ");
}//�޴� ��� �Լ� & �޴� ���ñ�� �Լ�
int Successmenu() {
    int x = 55;
    int y = 28;
    int menuIndex = 0;
    char menuItems[2][20] = { "���ư���","��   ��" };

    while (1) {
        // �޴� ������ ���
        for (int i = 0; i < 2; i++) {
            gotoxy(x, y + i);
            if (i == menuIndex) printf("> %s", menuItems[i]);
            else printf("  %s", menuItems[i]);
        }

        // �Է� ó��
        int n = S_keyControl();
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
                main(); // ���ư��⸦ �����ϸ� FirstScreen() �Լ��� �̵�
            }
            else if (menuIndex == 1) {
                exit(0); // ���Ḧ �����ϸ� ���α׷��� ����
            }
        }
        }
    }
}

int S_keyControl() {
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