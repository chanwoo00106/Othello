#include<stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<Windows.h>

#define RIGHT 77
#define LEFT 75
#define	TOP 72
#define BOTTOM 80
#define SPACEBAR 32

// 시작시 화면에 띄우기
void setView() {
	system("mode con:cols=100 lines=25");
	system("title test");
}

//화면에 띄우기
void view(int arr[8][8], int cursor[2]) {
	system("cls");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (cursor[0] == i && cursor[1] == j) printf("↖");
			else if (arr[i][j] == 0) printf("□");
			else if (arr[i][j] == 1) printf("●");
			else printf("○");
		}
		printf("\n");
	}
}


// 착수 함수
int start(int arr[8][8], int *turn, int cursor[]) {
	if (arr[cursor[0]][cursor[1]] == 0) {
		arr[cursor[0]][cursor[1]] = *turn;
		*turn = *turn == 2 ? 1 : 2;
	}
	else return 1;
	return 0;
}

// 커서 움직임
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

	setView(); // 크기 title

	while (1) {
		view(arr, cursor, turn);
		printf("%d\n\n", key);
		if (warning) printf("여기에는 착수가 불가 합니다");
		else if (!warning) printf("'q'를 누르면 종료됩니다.\n");

		key = _getch();
		if (key != SPACEBAR) move(cursor, key);
		else warning = start(arr, &turn, cursor);
		
	}
	return 0;
}