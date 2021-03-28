#define _CRT_SECURE_NO_WARNINGS
#include<bangtal.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

SceneID scene;
ObjectID game_board[12], original_board[12];
ObjectID startbutton, endbutton;
int blank = 11;

bool game = false;

TimerID timer;
float timeValue = 0.02f;    //퍼즐이 섞일때 한칸 움직이는데 걸리는 시간 - 속도
int mixCount;

clock_t starttime, endtime;

int indexToX(int i)
{
	return 243 + 200 * (i % 4);
}

int indexToY(int i)
{
	return  415 - 200 * (i / 4);
}

int game_index(ObjectID object)
{
	for (int i = 0; i < 12; i++)
	{
		if (game_board[i] == object)  return i;
	}
	return -1;
}

ObjectID changeImage(ObjectID origin, const char* image) {

	ObjectID change = createObject(image);

	setObjectImage(origin, image);
	showObject(origin);

	return change;
}

void game_move(int i)
{
	ObjectID object = game_board[i];
	game_board[i] = game_board[blank];
	locateObject(game_board[i], scene, indexToX(i), indexToY(i));
	game_board[blank] = object;
	locateObject(game_board[blank], scene, indexToX(blank), indexToY(blank));

	blank = i;
}

void game_print()
{
	for (int i = 0; i < 12; i++)
	{
		printf("%d ", game_board[i]);
	}
	printf("\n");
}

bool possible_move(int i)
{
	if (i % 4 > 0 && blank == i - 1) return true;
	if (i % 4 < 3 && blank == i + 1) return true;
	if (i / 4 > 0 && blank == i - 4) return true;
	if (i / 4 < 2 && blank == i + 4) return true;

	return false;
}

int random_move()
{
	int i = -1;   //not determined
	while (i == -1)
	{
		switch (rand() % 4)
		{
		case 0: if (blank % 4 > 0)
		{
			i = blank - 1;
			break;
		}
		case 1: if (blank % 4 < 3)
		{
			i = blank + 1;
			break;
		}
		case 2: if (blank / 4 > 0)
		{
			i = blank - 4;
			break;
		}
		case 3: if (blank / 4 < 2)
		{
			i = blank + 4;
			break;
		}
		}
	}

	return i;
}

bool game_end()  //게임이 종료되는 조건
{
	for (int i = 0; i < 12; i++)
	{
		if (game_board[i] != original_board[i])
		{
			return false;
		}
	}
	return true;
}

void game_start()
{
	blank = 11;
	hideObject(game_board[blank]);

	mixCount = 110;        //섞는 횟수

	setTimer(timer, timeValue);
	startTimer(timer);

	starttime = clock();
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (game)
	{
		int i = game_index(object);
		if (possible_move(i))
		{
			game_move(i);

			if (game_end())
			{
				game = false;
				changeImage(startbutton, "restart.png");
				showObject(endbutton);
				showObject(game_board[blank]);

				showMessage("completed");

				endtime = clock(); //끝났을 시간 측정
				double time = double(endtime - starttime) / CLOCKS_PER_SEC; //처음 시작 시간 - 끝난 시간 = 플레이시간
				char playtime[256];
				sprintf(playtime, "%0.1lf\n", time);
				showMessage(playtime);

				system("cls");
			}
			game_print();
		}
	}
	else
	{
		if (object == startbutton)
		{
			game_start();
		}
	}
}

void timerCallback(TimerID timer)
{
	game_move(random_move());

	mixCount--;
	if (mixCount > 0)
	{
		setTimer(timer, timeValue);
		startTimer(timer);
	}

	else
	{
		game = true;
		hideObject(startbutton);
	}

}

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown = true)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown)
	{
		showObject(object);
	}

	return object;
}

SceneID game_init()
{
	scene = createScene("시작화면", "game.png");

	char path[50];
	for (int i = 0; i < 12; i++)
	{
		sprintf(path, "%d.png", i + 1);
		game_board[i] = createObject(path, scene, indexToX(i), indexToY(i));
		original_board[i] = game_board[i];
	}

	startbutton = createObject("start.png", scene, 590, 100);

	timer = createTimer(timeValue);

	return scene;
}

int main()
{
	srand(time(NULL));

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	endbutton = createObject("end.png", scene, 590, 20, false);

	startGame(game_init());
}