//�_�i�ڰV�m�j�v
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
	cout << "��ξޱ��覡 1�GWASD, 2�G�W�U���k" << endl;
	rlutil::hidecursor();
	//���ϥΪ̿�ܾާ@�覡�Achar��WASD�Aint���W�U���k
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

