#include "stdafx.h"

#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <random>
#include <time.h>

using namespace std;

class tile {
public:
	enum bombPosition{
		bomb,
		empty
	};
	enum tileVisible {
		visible,
		invisible
	};
	enum bombCheck {
		bome,
		none
	};
	struct tileState {
		bombPosition gameBomb;
		tileVisible gameVisible;
		bombCheck gameBombCheck;
		int gameNumber;
		int viewCount;
	};
	vector<vector<tileState>> mainTile;
	void consoleSetting();
	void cinClear();
	void Difficulty();
	void startSetting();
	void start();
	void draw();
	void getEvent();
	void operation1();
	void operation2();
	void eventOperation();
	void detectBomb();
	void viewCountReset();
	void lost();
	void winTest();
	int difficulty;
	int lengthX;
	int lengthY;
	int userInputX;
	int userInputY;
	int lightingX;
	int lightingY;
	int userInputCommand;
	int random;
	int count;
	int repeatCount;
	bool onOff;
	bool first;
	bool detect;
};
//void gotoxy(int x, int y){
//    COORD pos = { x,y };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}
//void textcolor(int color_number){
//    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
//}
void tile::consoleSetting() {
	system("mode con cols=100 lines=30 | title 제목명");

}
void tile::cinClear() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
	}
}
void tile::Difficulty() {
	cinClear();
	cout << "난이도를 선택해주세요." << endl;
	cout << "쉬움: 1" << endl;
	cout << "보통: 2" << endl;
	cout << "어려움: 3" << endl;
	cout << "커스텀: 4" << endl;
	cin >> difficulty;
	if (difficulty == 4) {
		cout << "x축의 길이를 적어주세요: ";
		cin >> lengthX;
		cout << "y축의 길이를 적어주세요: ";
		cin >> lengthY;
	}
	else if (difficulty >= 1 && difficulty <= 3) {
		lengthX = difficulty * 8 - 1;
		lengthY = difficulty * 8 - 1;
	}
	else {
		system("cls");
		cout << "다시 입력해주세요" << endl;
		Difficulty();
	}
}
void tile::startSetting() {
	for (int i = 0; i < lengthY; i++) {
		vector<tileState> tiles(lengthX);
		mainTile.push_back(tiles);
		for (int j = 0; j < lengthX; j++) {
			random = rand() % (12 / difficulty);
			if (random == 1)
				mainTile[i][j].gameBomb = bomb;
			else
				mainTile[i][j].gameBomb = empty;
			mainTile[i][j].gameVisible = invisible;
			mainTile[i][j].gameBombCheck = none;
			mainTile[i][j].gameNumber = 0;
		}
	}
	mainTile[userInputX][userInputY].gameBomb = empty;
	first = true;
}
void tile::start() {
	winTest();
	draw();
	getEvent();
}
void tile::viewCountReset() {
	for (int i = 0; i < lengthX; i++) {
		for (int j = 0; j < lengthY; j++) {
			if (mainTile[i][j].gameBomb == bomb)
				mainTile[i][j].viewCount = 100;
			else
				mainTile[i][j].viewCount = 0;
		}
	}
}
void tile::draw() {
	system("cls");
	for (int i = -2; i < lengthY; i++) {
		for (int j = -2; j < lengthX; j++) {
			if (i == -2 && j == -2)
				cout << "  ";
			else if (i == -1 && j == -1)
				cout << "┼";
			else if (i == -1)
				cout << "──";
			else if (j == -1)
				cout << "│";
			else if (i == -2)
				cout << setw(2) << j + 1;
			else if (j == -2)
				cout << setw(2) << i + 1;
			else {
				if (mainTile[i][j].gameVisible == visible) {
					if (mainTile[i][j].gameBomb == empty) {
						if (mainTile[i][j].gameNumber == 0)
							cout << "□";
						else
							cout << setw(2) << mainTile[i][j].gameNumber;
					}
					else {
						cout << "®";
					}
				}
				else {
					if (mainTile[i][j].gameBombCheck == bome) {
						cout << "▣";
					}
					else {
						cout << "■";
					}
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}
void tile::getEvent() {
	cinClear();
	cout << "좌표 값 입력(x y):";
	cin >> userInputY >> userInputX;
	--userInputX;
	--userInputY;
	if ((userInputX >= 0 && userInputX <= lengthX) && (userInputY >= 0 && userInputX <= lengthY)){
		cout << endl;
		cout << "확인: 1" << endl;
		cout << "지뢰체크: 2 " << endl;
		cout << "수행할 작업 입력: ";
		cinClear();
		cin >> userInputCommand;
		if (userInputCommand == 1 || userInputCommand == 2) {
			if (userInputCommand == 1) {
				if (first == true){
					first = false;
					mainTile[userInputX][userInputY].gameBomb = empty;
				}
				operation1();
			}
			else if (userInputCommand == 2)
				operation2();
			start();
		}
	}
	start();
}
void tile::operation1() {//시야
	lightingX = userInputX;
	lightingY = userInputY;
	viewCountReset();
	repeatCount = 1;
	mainTile[lightingX][lightingY].viewCount = repeatCount;
	mainTile[lightingX][lightingY].gameVisible = visible;
	if (mainTile[lightingX][lightingY].gameBomb == bomb)
		lost();
	while (true) {
		for (int i = 0; i < lengthX; i++) {
			for (int j = 0; j < lengthY; j++) {
				if (mainTile[i][j].viewCount == repeatCount) {
					count = 0;
					for (int k = -1; k < 2; k++) {
						for (int l = -1; l < 2; l++) {
							if ((i + k != -1) && (j + l != -1) && (i + k != lengthX) && (j + l != lengthY)) {
								if (mainTile[i + k][j + l].gameBomb == bomb) {
									count++;
								}
							}
						}
					}
					mainTile[i][j].gameNumber = count;
					if (mainTile[i][j].gameNumber == 0) {
						if (i + 1< lengthX && mainTile[i + 1][j].viewCount == 0) {
							mainTile[i + 1][j].viewCount = repeatCount + 1;
							mainTile[i + 1][j].gameVisible = visible;
						}
						if (i>0 && mainTile[i - 1][j].viewCount == 0) {
							mainTile[i - 1][j].viewCount = repeatCount + 1;
							mainTile[i - 1][j].gameVisible = visible;
						}
						if (j + 1< lengthY && mainTile[i][j + 1].viewCount == 0) {
							mainTile[i][j + 1].viewCount = repeatCount + 1;
							mainTile[i][j + 1].gameVisible = visible;
						}
						if (j> 0 && mainTile[i][j - 1].viewCount == 0) {
							mainTile[i][j - 1].viewCount = repeatCount + 1;
							mainTile[i][j - 1].gameVisible = visible;
						}
					}
				}
			}
		}
		repeatCount++;
		if (repeatCount == 100)
			start();
	}
}
void tile::detectBomb() {

	mainTile[lightingX][lightingY].gameNumber = count;
}
void tile::operation2() {//지뢰표시
	if (mainTile[userInputX][userInputY].gameVisible == invisible){
		if (mainTile[userInputX][userInputY].gameBombCheck == none)
			mainTile[userInputX][userInputY].gameBombCheck = bome;
		else
			mainTile[userInputX][userInputY].gameBombCheck = none;
	}
}
void tile::lost() {
	system("cls");
	draw();
	cout << "패배" << endl;
	exit(0);
}
void tile::winTest() {
	detect = false;
	for (int i = 0; i < lengthX; i++) {
		for (int j = 0; j < lengthY; j++) {
			if (mainTile[i][j].gameBomb == empty) {
				if (mainTile[i][j].gameVisible == invisible) {
					detect = true;
				}
			}
		}
	}
	if (detect == false) {
		cout << "승리" << endl;
		exit(0);
	}
}

void tile::eventOperation() {

}
int main()
{
	srand((unsigned int)time(NULL));
	tile game;
	game.consoleSetting();
	game.Difficulty();
	game.startSetting();
	game.start();
}
