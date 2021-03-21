// Project3 퍼즐
#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

SceneID scene1, scene2;
ObjectID start, end1, end2, giveup;
ObjectID piece00, piece01, piece02, piece03, piece10, piece11, piece12, piece13, piece20, piece21, piece22, blank;
TimerID timer1, timer2;
int random, maplist[3][4], num[12] = { 0 };
clock_t starttime, endtime;

int boardX[3][4] = { //X좌표
	{243, 443, 643, 843},
	{243, 443, 643, 843},
	{243, 443, 643, 843}
};

int boardY[3][4] = { //Y좌표
	{415, 415, 415, 415},
	{215, 215, 215, 215},
	{15, 15, 15, 15}
};

ObjectID puzzle[3][4] = { //맨 처음에 퍼즐 설정하기
 {piece00, piece01, piece02, piece03},
 {piece10, piece11, piece12, piece13},
 {piece20, piece21, piece22, blank}
};

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}

	return object;
}

ObjectID changeImage(ObjectID origin, const char* image) {

	ObjectID change = createObject(image);

	setObjectImage(origin, image);
	showObject(origin);

	return change;
}

void Shift(ObjectID& a, ObjectID& b) //퍼즐 조각 움직이는 함수
{
	ObjectID tmp1 = a;
	a = b;
	b = tmp1;
}

void ShiftX(int& x1, int& x2) { //퍼즐 조각의 X좌표를 움직이는 함수
	int tmp2 = x1;
	x1 = x2;
	x2 = tmp2;
}

void ShiftY(int& y1, int& y2) { //퍼즐 조각의 Y좌표를 움직이는 함수
	int tmp3 = y1;
	y1 = y2;
	y2 = tmp3;
}

void puzzlemix() { //맨 처음 시작하자마자 퍼즐 섞기

	int n = 0, flag = 0;
	
	for (int i = 0; i < 3; i++) { //퍼즐 조각 12개에 0~11까지 번호 할당
		for (int j = 0; j < 4; j++) {
			puzzle[i][j] = n;
			n++;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d\t", puzzle[i][j]);
		}
	}
	printf("\n");

	//maplist에 임의로 0~11까지 배열
	while (flag != 12) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				random = rand() % 12;

				if (num[random] == 0) {
					num[random] = 1;
					maplist[i][j] = random;
					flag++;
				}
				else if (num[random] == 1) {
					j--;
					continue;
				}
			}
		}
	}

	//maplist와 비교하여 같은 값을 지닌 puzzle조각의 위치 변경 => 퍼즐 조각 섞기
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d\t", maplist[i][j]);
		}
		printf("\n");
	}

	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 4; l++) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					if (maplist[k][l] == puzzle[i][j]) {
						locateObject(puzzle[i][j], scene2, boardX[k][l], boardY[k][l]);
						showObject(puzzle[i][j]);
					}
				}
			}
		}
	}
}

void endGame(bool success) {

	if (success) {
		showMessage("퍼즐 맞추기 성공~~!");
	}
	else {
		showMessage("퍼즐 실패ㅠㅠ");
	}

	changeImage(start, "restart.png");
	showObject(end1);

	endtime = clock(); //끝났을 시간 측정
	double time = double(endtime - starttime) / CLOCKS_PER_SEC; //처음 시작 시간 - 끝난 시간 = 플레이시간
	char playtime[256];
	sprintf(playtime, "%0.1lf\n", time);
	showMessage(playtime);

	system("cls");
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (object == start) {
		hideObject(start);
		hideObject(end1);
		
		starttime = clock();

		enterScene(scene2);

		puzzlemix();
	}

	else if (object == end1) {
		endGame(false);
	}

	else if (object == end2) {
		enterScene(scene1);
		endGame(false);
	}

	else if (object == giveup) { //게임 중도 포기 버튼
		showMessage("퍼즐해결을 포기하실 건가요?");
		showObject(end2);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {

			if (object == puzzle[i][j] && puzzle[i][j] != blank) {
				if (i < 2 && puzzle[i + 1][j] == blank) { //아래칸이 공백일때
					Shift(puzzle[i][j], blank);
					ShiftX(boardX[i][j], boardX[i + 1][j]);
					ShiftY(boardY[i][j], boardY[i + 1][j]);

					locateObject(puzzle[i][j], scene2, boardX[i + 1][j], boardY[i + 1][j]);
					locateObject(puzzle[i + 1][j], scene2, boardX[i][j], boardY[i][j]);
				}

				else if (i > 0 && puzzle[i - 1][j] == blank) { //위칸이 공백일때
					Shift(puzzle[i][j], blank);
					ShiftX(boardX[i][j], boardX[i - 1][j]);
					ShiftY(boardY[i][j], boardY[i - 1][j]);

					locateObject(puzzle[i][j], scene2, boardX[i - 1][j], boardY[i - 1][j]);
					locateObject(puzzle[i - 1][j], scene2, boardX[i][j], boardY[i][j]);
				}

				else if (j < 3 && puzzle[i][j + 1] == blank) { //오른쪽칸이 공백일때
					Shift(puzzle[i][j], blank);
					ShiftX(boardX[i][j], boardX[i][j + 1]);
					ShiftY(boardY[i][j], boardY[i][j + 1]);

					locateObject(puzzle[i][j], scene2, boardX[i][j + 1], boardY[i][j + 1]);
					locateObject(puzzle[i][j + 1], scene2, boardX[i][j], boardY[i][j]);
				}

				else if (j > 0 && puzzle[i][j - 1] == blank) { //왼쪽칸이 공백일때
					Shift(puzzle[i][j], blank);
					ShiftX(boardX[i][j], boardX[i][j - 1]);
					ShiftY(boardY[i][j], boardY[i][j - 1]);

					locateObject(puzzle[i][j], scene2, boardX[i][j - 1], boardY[i][j - 1]);
					locateObject(puzzle[i][j - 1], scene2, boardX[i][j], boardY[i][j]);
				}

			}
		}
	}
}

int main() {

	srand(time(NULL));

	setMouseCallback(mouseCallback);

	scene1 = createScene("배경", "puzzle.png");
	scene2 = createScene("퍼즐", "game.png");

	puzzle[0][0] = createObject("조각1", "1.png", scene2, boardX[0][0], boardY[0][0], false);
	puzzle[0][1] = createObject("조각2", "2.png", scene2, boardX[0][1], boardY[0][1], false);
	puzzle[0][2] = createObject("조각3", "3.png", scene2, boardX[0][2], boardY[0][2], false);
	puzzle[0][3] = createObject("조각4", "4.png", scene2, boardX[0][3], boardY[0][3], false);
	puzzle[1][0] = createObject("조각5", "5.png", scene2, boardX[1][0], boardY[1][0], false);
	puzzle[1][1] = createObject("조각6", "6.png", scene2, boardX[1][1], boardY[1][1], false);
	puzzle[1][2] = createObject("조각7", "7.png", scene2, boardX[1][2], boardY[1][2], false);
	puzzle[1][3] = createObject("조각8", "8.png", scene2, boardX[1][3], boardY[1][3], false);
	puzzle[2][0] = createObject("조각9", "9.png", scene2, boardX[2][0], boardY[2][0], false);
	puzzle[2][1] = createObject("조각10", "10.png", scene2, boardX[2][1], boardY[2][1], false);
	puzzle[2][2] = createObject("조각11", "11.png", scene2, boardX[2][2], boardY[2][2], false);
	puzzle[2][3] = createObject("공백", "blank.png", scene2, boardX[2][3], boardY[2][3], false);

	start = createObject("시작", "start.png", scene1, 590, 70, true);
	end1 = createObject("종료", "end.png", scene1, 590, 20, true);
	end2 = createObject("종료", "end.png", scene2, 590, 20, false);
	giveup = createObject("게임포기", "end.png", scene2, 15, 645, true);

	startGame(scene1);
}