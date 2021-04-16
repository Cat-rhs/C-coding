#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

SceneID cleanupmain, explain, entrance, livingroom, bedroom1, bedroom2, kitchen, secretroom, hallway1, hallway2, desktopscreen; //장면생성
SceneID entrance_explain, livingroom_explain, bedroom1_explain, bedroom2_explain, kitchen_explain, secretroom_explain, hallway1_explain, hallway2_explain; //각 화면의 게임설명창
ObjectID cleanupstart, cleanupexplain, cleanupend, gameclear, gameend; //아이콘
ObjectID keypad, keypad1, keypad2, keypad3, bedroom1key, box, plant, bedroom1Quiz, bedroom2Quiz; //게임진행 아이템
ObjectID book, phone, battery, bag, wallet, charge, fullbag; //외출아이템
ObjectID explainleft, hallway1right, hallway2right, hallway2left, livingroomright, livingroomleft, secretroomleft, bedroom1up, bedroom2up, kitchenup, desktopleft; //공간이동 화살표
ObjectID entranceexplain, livingroomexplain, bedroom1explain, bedroom2explain, kitchenexplain, secretroomexplain, hallway1explain, hallway2explain; //게임설명 버튼
ObjectID entranceexplainleft, livingroomexplainleft, bedroom1explainleft, bedroom2explainleft, kitchenexplainleft, secretroomexplainleft, hallway1explainleft, hallway2explainleft; //게임설명창 나가기
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
		if (fullbag == getHandObject()) {
			showKeypad("153", keypad3);
		}
		else {
			showMessage("필요한 물건은 다 챙겼을까...?                                                                  <조합법 : 폰+보조배터리 = 충전 / 책+가방 -> 지갑+가방 -> 충전+가방 -> '꽉 찬 가방'!!>");
		}
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
	
	//외출 아이템
	if (object == book) {
		pickObject(book);
	}
	else if (object == phone) {
		pickObject(phone);
	}
	else if (object == battery) {
		pickObject(battery);
	}
	else if (object == bag) {
		pickObject(bag);
	}
	else if (object == wallet) {
		pickObject(wallet);
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

	//게임설명창
	if (object == entranceexplain) {
		enterScene(entrance_explain);
	}
	else if (object == livingroomexplain) {
		enterScene(livingroom_explain);
	}
	else if (object == bedroom1explain) {
		enterScene(bedroom1_explain);
	}
	else if (object == bedroom2explain) {
		enterScene(bedroom2_explain);
	}
	else if (object == kitchenexplain) {
		enterScene(kitchen_explain);
	}
	else if (object == secretroomexplain) {
		enterScene(secretroom_explain);
	}
	else if (object == hallway1explain) {
		enterScene(hallway1_explain);
	}
	else if (object == hallway2explain) {
		enterScene(hallway2_explain);
	}

	//게임설명창 나가기
	if (object == entranceexplainleft) {
		enterScene(entrance);
	}
	else if (object == livingroomexplainleft) {
		enterScene(livingroom);
	}
	else if (object == bedroom1explainleft) {
		enterScene(bedroom1);
	}
	else if (object == bedroom2explainleft) {
		enterScene(bedroom2);
	}
	else if (object == kitchenexplainleft) {
		enterScene(kitchen);
	}
	else if (object == secretroomexplainleft) {
		enterScene(secretroom);
	}
	else if (object == hallway1explainleft) {
		enterScene(hallway1);
	}
	else if (object == hallway2explainleft) {
		enterScene(hallway2);
	}

	//방 문
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
		hideObject(curtain);
	}
	else if (object == bookcase) {
		showMessage("책장정리를 하였다  종이가 떨어진 것 같다");
		showObject(bedroom1Quiz);
		hideObject(bookcase);
	}
	else if (object == sofa) {
		showMessage("소파쿠션정리를 하며 보조배터리를 찾았다..!! 휴대폰을 찾아 충전하자");
		showObject(battery);
		hideObject(sofa);
	}
	//방1
	else if (object == books) {
		showMessage("어제 읽던 책을 정리하였다  지갑을 찾았다..!!");
		showObject(wallet);
		hideObject(books);
	}
	else if (object == blanket) {
		showMessage("이불정리를 하며 휴대폰을 찾았다..!! 보조배터리를 찾아 충전하자");
		showObject(phone);
		hideObject(blanket);
	}
	//방2
	else if (object == clothes) {
		showMessage("옷장정리를 하고 옷을 입었다 가방을 챙겼다..!!");
		showObject(bag);
		hideObject(clothes);
	}
	else if (object == bookshelf) {
		showMessage("선반 위의 책을 정리하였다 필요한 책을 가방에 넣었다..!!");
		showObject(book);
		hideObject(bookshelf);
	}
	else if (object == desktop) {
		enterScene(desktopscreen);
	}
	//부엌
	else if (object == washing) {
		showMessage("설거지를 하였다");
		hideObject(washing);
	}
	else if (object == table) {
		showMessage("쪽지를 발견하였다...!!!");
		showObject(bedroom2Quiz);
		hideObject(table);
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
	desktopscreen = createScene("노트북화면", "desktopscreen.png");

	//각 화면의 게임설명창
	entrance_explain = createScene("게임설명창-현관", "explain.png");
	livingroom_explain = createScene("게임설명창-거실", "explain.png");
	bedroom1_explain = createScene("게임설명창-방1", "explain.png");
	bedroom2_explain = createScene("게임설명창-방2", "explain.png");
	kitchen_explain = createScene("게임설명창-부엌", "explain.png");
	secretroom_explain = createScene("게임설명창-비밀의 방", "explain.png");
	hallway1_explain = createScene("게임설명창-복도1", "explain.png");
	hallway2_explain = createScene("게임설명창-복도2", "explain.png");

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
	bedroom1key = createObject("방1의 열쇠", "bedroom1key.png", hallway1, 1000, 250, false);
	scaleObject(bedroom1key, 0.4f);

	plant = createObject("화분", "plant.png", hallway1, 900, 230, true);
	scaleObject(plant, 2.0f);
	bedroom1Quiz = createObject("방1퀴즈", "bedroom1Quiz.png", livingroom, 900, 280, false);
	scaleObject(bedroom1Quiz, 0.03f);
	bedroom2Quiz = createObject("방1퀴즈", "bedroom2Quiz.png", kitchen, 100, 100, false);
	scaleObject(bedroom2Quiz, 0.03f);

	//외출 아이템
	book = createObject("책", "book.png", bedroom2, 650, 460, false);
	scaleObject(book, 0.3f);
	phone = createObject("휴대폰", "phone.png", bedroom1, 600, 180, false);
	scaleObject(phone, 0.3f);
	battery = createObject("보조배터리", "battery.png", livingroom, 80, 250, false);
	scaleObject(battery, 0.3f);
	bag = createObject("가방", "bag.png", bedroom2, 1000, 10, false);
	scaleObject(bag, 0.7f);
	wallet = createObject("지갑", "wallet.png", bedroom1, 860, 220, false);
	scaleObject(wallet, 0.3f);
	charge = createObject("charge.png");
	fullbag = createObject("fullbag.png");

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

	//게임설명 버튼
	entranceexplain = createObject("게임설명-현관", "explainbutton.png", entrance, 10, 650, true);
	scaleObject(entranceexplain, 0.7f);
	livingroomexplain = createObject("게임설명-거실", "explainbutton.png", livingroom, 10, 650, true);
	scaleObject(livingroomexplain, 0.7f);
	bedroom1explain = createObject("게임설명-방1", "explainbutton.png", bedroom1, 10, 650, true);
	scaleObject(bedroom1explain, 0.7f);
	bedroom2explain = createObject("게임설명-방2", "explainbutton.png", bedroom2, 10, 650, true);
	scaleObject(bedroom2explain, 0.7f);
	kitchenexplain = createObject("게임설명-부엌", "explainbutton.png", kitchen, 10, 650, true);
	scaleObject(kitchenexplain, 0.7f);
	secretroomexplain = createObject("게임설명-비밀의 방", "explainbutton.png", secretroom, 10, 650, true);
	scaleObject(secretroomexplain, 0.7f);
	hallway1explain = createObject("게임설명-복도1", "explainbutton.png", hallway1, 10, 650, true);
	scaleObject(hallway1explain, 0.7f);
	hallway2explain = createObject("게임설명-복도2", "explainbutton.png", hallway2, 10, 650, true);
	scaleObject(hallway2explain, 0.7f);

	//게임설명창 나가기
	entranceexplainleft = createObject("현관으로 나가기", "left.png", entrance_explain, 10, 10, true);
	livingroomexplainleft = createObject("거실로 나가기", "left.png", livingroom_explain, 10, 10, true);
	bedroom1explainleft = createObject("방1로 나가기", "left.png", bedroom1_explain, 10, 10, true);
	bedroom2explainleft = createObject("방2로 나가기", "left.png", bedroom2_explain, 10, 10, true);
	kitchenexplainleft = createObject("부엌으로 나가기", "left.png", kitchen_explain, 10, 10, true);
	secretroomexplainleft = createObject("비밀의 방으로 나가기", "left.png", secretroom_explain, 10, 10, true);
	hallway1explainleft = createObject("복도1로 나가기", "left.png", hallway1_explain, 10, 10, true);
	hallway2explainleft = createObject("복도2로 나가기", "left.png", hallway2_explain, 10, 10, true);

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

	defineCombination(phone, battery, charge);
	defineCombination(book, bag, bag);
	defineCombination(wallet, bag, bag);
	defineCombination(charge, bag, fullbag);

	startGame(cleanupmain);
}