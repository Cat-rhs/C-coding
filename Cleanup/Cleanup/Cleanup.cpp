#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

SceneID cleanupmain, explain, clearscreen, entrance, livingroom, bedroom1, bedroom2, kitchen, secretroom, hallway1, hallway2, desktopscreen; //장면생성
ObjectID cleanupstart, cleanupexplain, cleanupend, gameclear, gameend; //아이콘
ObjectID keypad, keypad1, keypad2, keypad3, bedroom1key, box, plant, bedroom1Quiz, bedroom2Quiz; //게임진행 아이템
ObjectID book, phone, battery, bag, wallet; // 외출아이템
ObjectID explainleft, hallway1right, hallway2right, hallway2left, livingroomright, livingroomleft, secretroomleft, bedroom1up, bedroom2up, kitchenup, desktopleft; //공간이동 화살표
ObjectID bedroom1door, bedroom2door, kitchendoor; //방 문
ObjectID housein /*현관*/, curtain, bookcase, sofa /*거실*/, books, blanket /*방1*/, clothes, bookshelf, desktop /*방2*/, washing, table /*부엌*/; //느낌표
clock_t starttime, endtime;
bool br1closed = true, br2closed = true;

//오브젝트 생성 함수
ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return object;
}

//이미지변경 함수
ObjectID changeImage(ObjectID origin, const char* image) {

	ObjectID change = createObject(image);

	setObjectImage(origin, image);
	showObject(origin);

	return change;
}

//게임시작 함수
void gamestart() {

}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	//메인화면 세팅
	if (object == cleanupstart) {
		clock_t start = clock();
		enterScene(entrance);
	}
	else if (object == cleanupexplain) {
		enterScene(explain);
	}
	else if (object == cleanupend) {
		endGame();
	}

	//게임진행 아이템
	//키패드에 퀴즈의 비밀번호를 누르면 현관문이 열린다
	if (object == keypad) {
		showKeypad("428", housein);
	}
	//키패드에 퀴즈1의 비밀번호를 누르면 상자가 열쇠로 바뀐다
	else if(object == keypad1) {
		showKeypad("5699", box);
	}
	//키패드에 퀴즈2의 비밀번호를 누르면 방2의 문이 열린다
	else if (object == keypad2) {
		showKeypad("240", bedroom2door);
	}
	//키패드에 퀴즈3의 비밀번호를 누르면 비밀의 방 문이 열리고 게임 클리어 화면으로 넘어간다
	else if (object == keypad3) {
		showKeypad("153", keypad3);
	}

	//방1문의 열쇠를 누르면 열쇠를 줍는다
	if (object == bedroom1key) {
		pickObject(bedroom1key);
	}

	//화분움직이면 상자가 보이게
	if (object == plant) {
		locateObject(plant, hallway1, 1080, 230);
		scaleObject(plant, 2.0f);
		showObject(plant);
	}
	//방1문의 퀴즈 쪽지를 누르면 쪽지를 줍는다
	else if (object == bedroom1Quiz) {
		pickObject(bedroom1Quiz);
	}
	//방2문의 퀴즈 쪽지를 누르면 쪽지를 줍는다
	else if (object == bedroom2Quiz) {
		pickObject(bedroom2Quiz);
	}
	
	//공간이동 화살표
	//설명화면에서 메인화면으로
	if (object == explainleft) {
		enterScene(cleanupmain);
	}
	//복도1에서 거실로
	else if (object == hallway1right) {
		enterScene(livingroom);
	}
	//복도2에서 비밀의 방으로
	else if (object == hallway2right) {
		enterScene(secretroom);
	}
	//복도2에서 거실로
	else if (object == hallway2left) {
		enterScene(livingroom);
	}
	//거실에서 복도2로
	else if (object == livingroomright) {
		enterScene(hallway2);
	}
	//거실에서 복도1로
	else if (object == livingroomleft) {
		enterScene(hallway1);
	}
	//비밀의 방에서 복도2로
	else if (object == secretroomleft) {
		enterScene(hallway2);
	}
	//방1을 나가서 복도1로
	else if (object == bedroom1up) {
		enterScene(hallway1);
	}
	//방2를 나가서 복도2로
	else if (object == bedroom2up) {
		enterScene(hallway2);
	}
	//부엌을 나가서 복도2로
	else if (object == kitchenup) {
		enterScene(hallway2);
	}
	///노트북화면을 나가서 방2로
	else if (object == desktopleft) {
		enterScene(bedroom2);
	}

	//방1 문
	if (object == bedroom1door) {
		if (br1closed) {
			if (bedroom1key == getHandObject()) {
				setObjectImage(object, "door-right-open.png");
				br1closed = false;
			}
			else {
				showMessage("거실 책장에서 힌트를 찾아보자!!");
			}
		}
		else {
			enterScene(bedroom1);
		}
	}
	//방2 문
	else if (object == bedroom2door) {
		if (br2closed == true) {
			showMessage("부엌을 뒤져보자..!! 어딘가에 두고 온 것 같다...");
		}
		else {
			changeImage(bedroom2door, "door-right-open.png");
			enterScene(bedroom2);
		}
	}
	//부엌 문
	else if (object == kitchendoor) {
		enterScene(kitchen);
	}

	//느낌표
	//현관
	if (object == housein) {
		showMessage("<퀴즈>                                                                                     [ 717-721-473-217-???-753-576-427-749 ]                                         ???에 들어갈 숫자는?");
	}
	//거실
	else if (object == curtain) {
		showMessage("커튼정리를 하였다");
	}
	else if (object == bookcase) {
		showMessage("책장정리를 하였다  종이가 떨어진 것 같다");
		showObject(bedroom1Quiz);
	}
	else if (object == sofa) {
		showMessage("소파쿠션정리를 하였다  보조배터리를 찾았다..!!");
	}
	//방1
	else if (object == books) {
		showMessage("어제 읽던 책을 정리하였다  지갑을 찾았다..!!");
	}
	else if (object == blanket) {
		showMessage("이불정리를 하였다  휴대폰을 찾았다..!!");
	}
	//방2
	else if (object == clothes) {
		showMessage("옷장정리를 하고 옷을 입었다 가방을 챙겼다..!!");
	}
	else if (object == bookshelf) {
		showMessage("선반 위의 책을 정리하였다 필요한 책을 가방에 넣었다..!!");
	}
	else if (object == desktop) {
		enterScene(desktopscreen);
	}
	//부엌
	else if (object == washing) {
		showMessage("설거지를 하였다");
	}
	else if (object == table) {
		showMessage("쪽지를 발견하였다...!!!");
		showObject(bedroom2Quiz);
	}

	/*
	//게임클리어
	if (object == gameclear) {
		endtime = clock(); //끝났을 시간 측정
		double time = double(endtime - starttime) / CLOCKS_PER_SEC; //처음 시작 시간 - 끝난 시간 = 플레이시간
		char playtime[256];
		sprintf(playtime, "%0.1lf\n", time);
		showMessage(playtime);

		system("cls");

		hideObject(gameclear);
		showObject(gameend);
	}
	*/
	//게임끝
	if (object == gameend) {
		endGame();
	}
	

}

void objectCallback(ObjectID object, EventID event) {

	//키패드를 풀면 복도1로 이동
	if (object == housein) {
		if (event == EventID::EVENT_KEYPAD) {
			enterScene(hallway1);
		}
	}
	//키패드1을 풀면 박스가 방1문 열쇠로 바뀐다
	else if (object == box) {
		if (event == EventID::EVENT_KEYPAD) {
			hideObject(box);
			hideObject(keypad1);
			showObject(bedroom1key);
			showMessage("잠금 해제!!");
		}
	}
	//키패드2를 풀면 방2문이 열린다
	else if (object == bedroom2door) {
		if (event == EventID::EVENT_KEYPAD) {
			br2closed = false;
			showMessage("문이 열렸다...!!");
			changeImage(bedroom2door, "door-right-open.png");
		}
	}
	//키패드3을 풀면 클리어화면으로 넘어간다
	else if (object == keypad3) {
		if (event == EventID::EVENT_KEYPAD) {
			endtime = clock(); //끝났을 시간 측정
			double time = double(endtime - starttime) / CLOCKS_PER_SEC; //처음 시작 시간 - 끝난 시간 = 플레이시간
			char playtime[256];
			sprintf(playtime, "%0.1lf 초만에 필요한 물건을 챙겨서 집을 나섰다..!!!\n", time);
			showMessage(playtime);

			system("cls");

			showObject(gameend);
		}
	}
}

int main() {
	setMouseCallback(mouseCallback);
	setObjectCallback(objectCallback);

	//장면 생성
	cleanupmain = createScene("메인화면", "cleanupmain.png");
	explain = createScene("게임설명", "explain.png");
	entrance = createScene("현관문", "entrance.png");
	livingroom = createScene("거실", "livingroom.png");
	bedroom1 = createScene("방1", "bedroom1.png");
	bedroom2 = createScene("방2", "bedroom2.png");
	kitchen = createScene("부엌", "kitchen.png");
	secretroom = createScene("비밀의 방", "secretroom.png");
	hallway1 = createScene("복도1", "hallway1.png");
	hallway2 = createScene("복도2", "hallway2.png");
	bedroom1Quiz = createScene("쪽지", "bedroom1Quiz.png");
	desktopscreen = createScene("노트북화면", "desktopscreen.png");

	//아이콘
	cleanupstart = createObject("시작버튼", "cleanupstart.png", cleanupmain, 590, 400, true);
	cleanupexplain = createObject("게임설명", "cleanupexplain.png", cleanupmain, 590, 360, true);
	cleanupend = createObject("게임종료", "cleanupend.png", cleanupmain, 590, 320, true);
	

	//게임진행 아이템
	keypad = createObject("퀴즈-현관", "keypad.png", entrance, 420, 310, true);
	scaleObject(keypad, 2.0f);
	box = createObject("상자", "box.png", hallway1, 1000, 250, true);
	scaleObject(box, 0.3f);
	keypad1 = createObject("퀴즈1-방1", "keypad.png", hallway1, 1030, 280, true);
	scaleObject(keypad1, 2.0f);
	keypad2 = createObject("퀴즈2-방2", "keypad.png", hallway2, 770, 420, true);
	scaleObject(keypad2, 2.0f);
	keypad3 = createObject("퀴즈3-비밀의문", "keypad.png", secretroom, 570, 360, true);
	scaleObject(keypad3, 2.0f);
	bedroom1key = createObject("방1의 열쇠", "bedroom1key.png", hallway1, 1000, 280, false);
	scaleObject(bedroom1key, 0.5f);

	plant = createObject("화분", "plant.png", hallway1, 900, 230, true);
	scaleObject(plant, 2.0f);
	bedroom1Quiz = createObject("방1퀴즈", "bedroom1Quiz.png", livingroom, 900, 280, false);
	scaleObject(bedroom1Quiz, 0.03f);
	bedroom2Quiz = createObject("방1퀴즈", "bedroom2Quiz.png", kitchen, 100, 100, false);
	scaleObject(bedroom2Quiz, 0.03f);

	//공간이동 화살표
	explainleft = createObject("메인화면으로 나가기", "left.png", explain, 10, 10, true);
	hallway1right = createObject("복도1-오른쪽 거실", "right.png", hallway1, 1170, 360, true);
	hallway2right = createObject("복도2-오른쪽 비밀의 방", "right.png", hallway2, 1170, 360, true);
	hallway2left = createObject("복도2-왼쪽 거실", "left.png", hallway2, 10, 360, true);
	livingroomright = createObject("거실-오른쪽 복도2", "right.png", livingroom, 1170, 360, true);
	livingroomleft = createObject("거실-왼쪽 복도1", "left.png", livingroom, 10, 360, true);
	secretroomleft = createObject("비밀의 방-왼쪽 복도2", "left.png", secretroom, 10, 360, true);
	bedroom1up = createObject("방1나가기-복도1", "up.png", bedroom1, 590, 650, true);
	bedroom2up = createObject("방2나가기-복도2", "up.png", bedroom2, 590, 650, true);
	kitchenup = createObject("부엌나가기-복도2", "up.png", kitchen, 590, 650, true);
	desktopleft = createObject("노트북화면 나가기", "left.png", desktopscreen, 10, 10, true);

	//방 문
	bedroom1door = createObject("방1문", "door-right-closed.png", hallway1, 800, 280, true);
	bedroom2door = createObject("방2문", "door-right-closed.png", hallway2, 800, 280, true);
	kitchendoor = createObject("부엌문", "door-left-closed.png", hallway2, 320, 270, true);

	//느낌표
	housein = createObject("현관퀴즈", "warning.png", entrance, 440, 310, true);
	curtain = createObject("커튼정리", "warning.png", livingroom, 200, 550, true);
	bookcase = createObject("책장정리", "warning.png", livingroom, 950, 500, true);
	sofa = createObject("소파쿠션정리", "warning.png", livingroom, 80, 300, true);
	books = createObject("책들정리", "warning.png", bedroom1, 850, 240, true);
	blanket = createObject("이불정리", "warning.png", bedroom1, 650, 180, true);
	clothes = createObject("옷장정리", "warning.png", bedroom2, 1000, 360, true);
	bookshelf = createObject("선반책정리", "warning.png", bedroom2, 600, 500, true);
	desktop = createObject("노트북-비밀의 방 퀴즈", "warning.png", bedroom2, 150, 300, true);
	washing = createObject("설거지", "warning.png", kitchen, 1000, 330, true);
	table = createObject("방2퀴즈", "warning.png", kitchen, 100, 50, true);


	gameend = createObject("게임끝", "cleanupend.png", secretroom, 410, 360, false);
	scaleObject(gameend, 5.0f);

	startGame(cleanupmain);
}