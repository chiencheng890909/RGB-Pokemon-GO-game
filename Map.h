#pragma once
#ifndef MAP_H
#define MAP_H
#include<vector>
#include<string>
#include<exception>
#include "rlutil.h"

using namespace std;

class Map {
private:
	vector<string> map;
	int** CM;//放置屏障
	void LoadMap();
public:
	Map();
	void printMap();//螢幕上印出地圖
	bool check(int i, int j);//確定玩家移動的目標是否允許移動
	char GetAttributes(int i, int j);//確定玩家移動的目標在螢幕上的符號
	//攻略完道館後使用，將'#'改成'X'並賦予不可靠近屬性
	void SetMap(int i, int j, char X) { map[j - 1][i - 1] = X; CM[j - 1][i - 1] = 1; }
	
};
#endif // !MAP_H

