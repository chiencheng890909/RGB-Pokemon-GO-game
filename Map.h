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
	int** CM;//��m�̻�
	void LoadMap();
public:
	Map();
	void printMap();//�ù��W�L�X�a��
	bool check(int i, int j);//�T�w���a���ʪ��ؼЬO�_���\����
	char GetAttributes(int i, int j);//�T�w���a���ʪ��ؼЦb�ù��W���Ÿ�
	//�𲤧��D�]��ϥΡA�N'#'�令'X'�ýᤩ���i�a���ݩ�
	void SetMap(int i, int j, char X) { map[j - 1][i - 1] = X; CM[j - 1][i - 1] = 1; }
	
};
#endif // !MAP_H

