#include "Map.h"
#include <fstream>

Map::Map()
{
	LoadMap();
	//檢測map內哪裡可走(0)，哪裡不可走(1)
	CM = new int* [map.size()]();
	for (unsigned int i = 0; i < map.size(); i++) {
		CM[i] = new int[map[i].length()]();
		for (unsigned int j = 0; j < map[i].length(); j++) {
			if (map[i][j] == '*')
				CM[i][j] = 1;
			else if (map[i][j] == '!')
				CM[i][j] = 1;
			else if (map[i][j] >= '1' && map[i][j] <= '9')
				CM[i][j] = 1;
			else if (map[i][j] >= 'A' && map[i][j] <= 'D')
				CM[i][j] = 1;
		}
	}
	/*for (unsigned int i = 0; i < map.size(); i++) {
		for (unsigned int j = 0; j < map[i].length(); j++) {
			cout << CM[i][j];
		}
		cout << endl;
	}*/
}

void Map::LoadMap()
{
	string Input;
	ifstream inFile("C:/Users/user/Desktop/C++實習專題/C++實習專題/termproj/assets/yzumap.txt", ios::in);
	while (getline(inFile,Input,'\n')) {
		map.push_back(Input);
		Input.clear();
	}
	inFile.close();
}

void Map::printMap()
{
	rlutil::saveDefaultColor();
	for (unsigned int i = 0; i < map.size(); i++) {
		for (unsigned int j = 0; j < map[i].length(); j++) {
			if(map[i][j]==';')
				rlutil::setColor(10);
			else if (map[i][j] == '!')
				rlutil::setColor(8);
			else if (map[i][j] == '~')
				rlutil::setColor(9);
			else if (map[i][j] == '#')
				rlutil::setColor(14);
			cout << map[i][j];
			rlutil::resetColor();
		}
		cout << endl;
	}
		
}

bool Map::check(int i, int j)
{
	if (CM[j - 1][i - 1] == 1)
		return false;
	return true;
}

char Map::GetAttributes(int i, int j)
{
	return map[j - 1][i - 1];
}
