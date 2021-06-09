#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<Windows.h>

#define RIGHT 77
#define LEFT 75
#define	TOP 72
#define BOTTOM 80
#define SPACEBAR 32

void setView() {
	system("mode con:cols=100 lines=25");
	system("title test");
}

void view(int arr[8][8], int cursor[2]) {
	system("cls");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (cursor[0] == i && cursor[1] == j) printf("��");
			else if (arr[i][j] == 0) printf("��");
			else if (arr[i][j] == 1) printf("��");
			else printf("��");
		}
		printf("\n");
	}
}

void reverse() {

}

// ���� ���� ����
void option(int arr[8][8], int cursor[], int order) {
	int turn = order == 1 ? 2 : 1;
	int x = cursor[0], y = cursor[1];
	int position[3][3] = { 0 };
	
	//������ ��
	if (x == 0 && y == 7) {
		position[0][2] = 1;
		position[0][1] = 1;
		position[0][0] = 1;
		position[1][2] = 1;
		position[2][2] = 1;
	}

	//���� ��
	else if (x == 0 && y == 0) {
		position[2][0] = 1;
		position[1][0] = 1;
		position[0][0] = 1;
		position[0][1] = 1;
		position[0][2] = 1;
	}

	//������ �Ʒ�
	else if (x == 7 && y == 7) {
		position[0][2] = 1;
		position[1][2] = 1;
		position[2][2] = 1;
		position[2][1] = 1;
		position[2][0] = 1;
	}

	//���� �Ʒ�
	else if (x == 7 && y == 0) {
		position[0][0] = 1;
		position[1][0] = 1;
		position[2][0] = 1;
		position[2][1] = 1;
		position[2][2] = 1;
	}

	// �� ��
	else if (y == 0) {
		position[0][1] = 1;
		position[0][0] = 1;
		position[0][2] = 1;
	}

	//������ ��
	else if (x == 7) {
		position[0][2] = 1;
		position[1][2] = 1;
		position[2][2] = 1;
	}

	//���� ��
	else if (x == 0) {
		position[0][0] = 1;
		position[1][0] = 1;
		position[2][0] = 1;
	}

	//�Ʒ� ��
	else if (y == 7) {
		position[2][0] = 1;
		position[2][1] = 1;
		position[2][2] = 1;
	}

	//-------------------------

	if (!position[0][0]) {// ���� �������������̤ӤӤ���
		int j = y - 2;
		for (int i = x - 2; i > 0; i--) {
			if (arr[i][j] == order) {
				for (++i; i < x; i++) {
					j++;
					arr[i][j] = turn;
				}
				break;
			}
			if (j == 0) break;
			j--;
		}
	}

	if (!position[0][1]) { //�����������̤��̤��̤�����
		for (int i = y - 1; i >= 0; i--) {
			if (arr[x][i] == order) {
				for (++i; i < y; i++) {
					arr[x][i] = turn;
				}
				break;
			}
		}
	}

	if (!position[0][2]) { // �� �����ɿ��������Ǥ�
		int j = y - 2;
		for (int i = x + 2; i <= 7; i++) {
			if (arr[i][j] == order) {
				for (++i; i > x; i--) {
					j++;
					arr[i][j] = turn;
				}
				break;
			}
			if (j == 0) break;
			j--;
		}
	}

	if (!position[1][0]) { // ���ɿ������ǿ�
		for (int i = x - 2; i >= 0; i--) {
			if (arr[i][y] == order) {
				for (++i; i < x; i++) {
					arr[i][y] = turn;
				}
				break;
			}
		}
	}

	if (!position[1][2]) { // �����ɿ������Ǥ���
		for (int i = x + 2; i <= 7; i++) {
			if (arr[i][y] == order) {
				for (i; i > x; i--) {
					arr[i][y] = turn;
				}
				break;
			}
		}
	}

	if (!position[2][0]) {}
	if (!position[2][1]) {}
	if (!position[2][2]) {}
}

// ���� �Լ�
int start(int arr[8][8], int *turn, int cursor[]) {
	if (arr[cursor[0]][cursor[1]] == 0) {
		arr[cursor[0]][cursor[1]] = *turn;

		if (*turn == 1) *turn = 2;
		else *turn = 1;
	}
	else return 1;
	return 0;
}

void move(int cursor[], int key) {
	switch (key) {
	case RIGHT:
		if (cursor[1] != 7) ++cursor[1];
		break;
	case LEFT:
		if (cursor[1] != 0) --cursor[1];
		break;
	case BOTTOM:
		if (cursor[0] != 7) ++cursor[0];
		break;
	case TOP:
		if (cursor[0] != 0) --cursor[0];
		break;
	case 81:
	case 113:
		exit(1);
	}
}

// black : 2
// white : 1

int main() {
	int key = 0, turn = 2, cursor[2] = {0, 0}, warning = 0;
	int arr[8][8] = {
		{0},
		{0},
		{0},
		{0,0,0,1,2},
		{0,0,0,2,1},
		{0},
		{0},
		{0}
	};

	setView(); // ũ�� title

	while (1) {
		view(arr, cursor, turn);
		printf("%d\n\n", key);
		if (warning) printf("���⿡�� ������ �Ұ� �մϴ�");
		else if (!warning) printf("'q'�� ������ ����˴ϴ�.");

		key = _getch();
		if (key != SPACEBAR) move(cursor, key);
		else warning = start(arr, &turn, cursor);
		
	}
	return 0;
}