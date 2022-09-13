//寶可夢訓練大師
#include<iostream>

#include "rlutil.h"
#include "pokemon.h"
#include "Map.h"
#include "Race.h"

using namespace std;

int main() {
	rlutil::saveDefaultColor();
	srand(time(NULL));
	char k;
	cout << "選用操控方式 1：WASD, 2：上下左右" << endl;
	rlutil::hidecursor();
	//讓使用者選擇操作方式，char為WASD，int為上下左右
	while (true) {
		k = rlutil::getkey();
		if (k == '1') {
			Race<char> theGame;
			theGame.Execute();
			break;
		}
		else if (k == '2') {
			Race<int> theGame;
			theGame.Execute();
			break;
		}
	}
	
	system("pause");
}

