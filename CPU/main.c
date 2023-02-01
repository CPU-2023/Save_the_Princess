#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "console.h"

struct Player {
	int speed;
	float x, y;
	int life;
};

struct Bullet {
	int x, y;
	int is_fired;	//�߻� ����
};
struct Player {
	int speed;
	float x, y;
	int life;
};

struct Bullet {
	int x, y;
	int is_fired;	//�߻� ����
};

const int BULLET_NUM = 50;

int main() {


	struct Player player;
	player.speed = 10;		//TODO: player_speed�ذ��ϱ�.
	player.x = 60;
	player.y = 15;
	player.life = 3;

	struct Bullet bullet;	//TODO: bullet ������ �������� ����.
	bullet.is_fired = 0;
	bullet.x = 0;
	bullet.y = 0;


	long start_time = clock();	// ���� ���� �ð�
	long spent_time;			// ���� ���� �ð�
	int fired_time = 0;
	while (1) {

		Clear();

		if (GetAsyncKeyState(VK_LEFT)) {
			player.x--;
			if (player.x < 0) {
				player.x = 0;
			}
		}

		if (GetAsyncKeyState(VK_RIGHT)) {
			player.x++;
			if (player.x > 119) {
				player.x = 119;
			}
		}
		if (GetAsyncKeyState(VK_UP)) {
			player.y--;
			if (player.y < 0) {
				player.y = 0;
			}
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			player.y++;
			if (player.y > 29) {
				player.y = 29;
			}
		}
		if (GetAsyncKeyState(VK_SPACE)) {

			if (!bullet.is_fired)
			{
				bullet.x = player.x;
				bullet.y = player.y - 1;
				bullet.is_fired = 1;	//ȭ���� �߻� �ɶ�
			}
		}
		if (bullet.is_fired)	//ȭ�� �߻� ����
		{
			gotoxy(bullet.x, bullet.y);
			printf("��");
			bullet.y--;
			if (bullet.y < 0)
			{
				bullet.is_fired = 0;
			}
		}
		gotoxy(player.x, player.y);
		printf("��");
		Sleep(50);
	}

	system("pause");
	return 0;
}