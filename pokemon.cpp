#include <iostream>
#include <fstream> 
#include <sstream>
#include "pokemon.h"

using namespace std;

static string Abilities[13] = { "Normal","Heal","Burning","Counter Attack" ,"Immunology" ,"Leech Life" ,
"Avoid","Double Attack" ,"Poison" ,"Lower Speed" ,"Rock Skin" ,"Lower Defence" ,"Lower Attack" };

static string AllofTypes[18] = { "Normal","Fire","Water","Electric","Grass","Ice","Fighting"
,"Poison","Ground","Flying","Psychic","Bug","Rock","Ghost","Dragon","Dark","Steel","Fairy"};

Icon::Icon(string Input)
{
	int x = 0;
	if (Input.size() == 1) {
		Sets.push_back(-1);
		TheWords = Input;
	}
	else if (Input[0] == '0'&& Input[1] == 'm') {
		Sets.push_back(-1);
		TheWords = "\n";
	}
	else {
		while (true) {
			while (Input[x] != ';') {
				if (Input[x] == 'm')
					break;
				if (Input[x + 1] <= '9' && Input[x + 1] >= '0') {
					Sets.push_back((Input[x] - '0') * 10 + (Input[x + 1]) - '0');
					x += 2;
				}
				else if (Input[x] <= '9' && Input[x] >= '0') {
					Sets.push_back(Input[x] - '0');
					x++;
				}
			}
			if (Input[x] == 'm')
				break;
			else
				x++;
		}
		x += 1;
		
		for (; x < Input.size()-1; x++)
				TheWords.push_back(Input[x]);
	}
}

pokemonData::pokemonData(){
	ReadIcons();
	ReadInformations();
	ReadTypes();
}

double pokemonData::GetCoefficientofType(int i, int j)
{
	return Types[i][j];
}

void pokemonData::ReadIcons(){
	string Location = "C:/Users/user/Desktop/C++��߱M�D/C++��߱M�D/termproj/assets/icons/color/";
	string Type = ".txt";
	string Num = "001";
	string Read;
	
	for (int i = 0; i < 32; i++) {
		vector <Icon> New;
		Icons.push_back(New);
		Read = "";
		ifstream inFile(Location + Num + Type, ios::in);//Ū��

		if (!inFile)//��Ū�����ɮסA��ܿ��~
		{
			std::cout << "File could not be opened" << endl;
			system("pause");
			exit(1);
		}
		while (!inFile.eof()){//���OŪ�i�U��m
			getline(inFile, Read, '[');
			Icons[i].push_back(Icon(Read));
		}
		Num[2] += 1;
		for (unsigned int j = Num.size() - 1; j + 1 > 0; j--) {
			if (Num[j] >= 58) {
				Num[j] -= 10;
				Num[j - 1] += 1;
			}
		}
		inFile.close();
	}
}

void pokemonData::ReadTypes()
{
	string Location = "C:/Users/user/Desktop/C++��߱M�D/C++��߱M�D/termproj/assets/type.csv";
	string Read;
	double read;
	ifstream inFile(Location, ios::in);

	if (!inFile)//��Ū�����ɮסA��ܿ��~
	{
		std::cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	while (getline(inFile, Read, ',')) {
		vector <double> New;
		if (Read.size() == 3)
			read = 0.5;
		else
			read = Read[0] - '0';
		New.push_back(read);
		for (int i = 0; i < 16; i++) {
			getline(inFile, Read, ',');
			if (Read.size() == 3)
				read = 0.5;
			else
				read = Read[0] - '0';
			New.push_back(read);
		}
		getline(inFile, Read, '\n');
		if (Read.size() == 3)
			read = 0.5;
		else
			read = Read[0] - '0';
		New.push_back(read);
		Types.push_back(New);
	}
	inFile.close();

}

void pokemonData::ReadInformations()
{
	string Location = "C:/Users/user/Desktop/C++��߱M�D/C++��߱M�D/termproj/assets/pokemons.csv";
	string Read, Name, Type;
	int HP, ATK, DEF, Speed, Ability;
	ifstream inFile(Location, ios::in);
	if (!inFile)//��Ū�����ɮסA��ܿ��~
	{
		std::cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	int x=0;
	stringstream sn;
	sn.str("");
	while (getline(inFile, Read, ',')) {
		x++;
		if (x == 33)
			break;
		getline(inFile, Name, ',');
		getline(inFile, Type, ',');
		getline(inFile, Read, ',');
		sn.clear();
		sn << Read;
		sn >> HP;
		getline(inFile, Read, ',');
		sn.clear();
		sn << Read;
		sn >> ATK;
		getline(inFile, Read, ',');
		sn.clear();
		sn << Read;
		sn >> DEF;
		getline(inFile, Read, ',');
		sn.clear();
		sn << Read;
		sn >> Speed;
		getline(inFile, Read, '\n');
		sn.clear();
		sn << Read;
		sn >> Ability;
		Information New(Name, Type, HP, ATK, DEF, Speed, Ability);

		Informations.push_back(New);
	}
	inFile.close();
}

vector<Icon> pokemonData::GetIcon(int choice)
{
	return Icons[choice];
}

Information pokemonData::GetInformation(int choice)
{
	return Informations[choice];
}

void pokemon::PrintIcon(int X,int Y)
{
	int Size = TheIcon.size();
	int y = 0;
	gotoxy(X, Y);

	for (int i = 0; i < Size; i++) {
		if (TheIcon[i].GetSize() == 1 && TheIcon[i].GetSets(0) == -1) {
			rlutil::resetColor();
			std::cout << TheIcon[i].GetTheWords();
			if (TheIcon[i].GetTheWords() == "\n") {
				Y++;
				gotoxy(X, Y);
			}
		}
		else {
			if (TheIcon[i].GetSets(TheIcon[i].GetSize() - 1) == 41)
				rlutil::setBackgroundColor(4);
			else if (TheIcon[i].GetSets(TheIcon[i].GetSize() - 1) == 43)
				rlutil::setBackgroundColor(6);
			else if (TheIcon[i].GetSets(TheIcon[i].GetSize() - 1) == 44)
				rlutil::setBackgroundColor(1);
			else if (TheIcon[i].GetSets(TheIcon[i].GetSize() - 1) == 46)
				rlutil::setBackgroundColor(3);
			else
				rlutil::setBackgroundColor(TheIcon[i].GetSets(TheIcon[i].GetSize() - 1) - 40);


			if (TheIcon[i].GetSets(1) == 1)
				y = 8;
			if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 30)
				rlutil::setColor(0 + y);
			else if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 31)
				rlutil::setColor(4 + y);
			else if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 32)
				rlutil::setColor(2 + y);
			else if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 33)
				rlutil::setColor(6 + y);
			else if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 34)
				rlutil::setColor(1 + y);
			else if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 35)
				rlutil::setColor(5 + y);
			else if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 36)
				rlutil::setColor(3 + y);
			else if ((TheIcon[i].GetSets(TheIcon[i].GetSize() - 2)) == 37)
				rlutil::setColor(7 + y);
			y = 0;
			std::cout << TheIcon[i].GetTheWords();
			if (TheIcon[i].GetTheWords() == "\n") {
				Y++;
				gotoxy(X, Y);
			}
		}
		rlutil::resetColor();
	}
}

void pokemon::PrintInformation(int X, int Y)
{
	gotoxy(X, Y);
	std::cout << "�W�١G" << TheInformation.getName();
	Y++;

	gotoxy(X, Y);
	std::cout << "�ݩʡG" << TheInformation.getType();
	Y++;

	gotoxy(X, Y);
	std::cout << "��q�G";
	if (TheInformation.getHP() >= 0 && TheInformation.getHP() < 10)
		cout << "0" << TheInformation.getHP() << "/" << TheInformation.getMaxHP() << "  " << "�����O�G" << TheInformation.getATK();
	else {
		cout << TheInformation.getHP() << "/" << TheInformation.getMaxHP() << "  " << "�����O�G" << TheInformation.getATK();
	}
	Y++;

	gotoxy(X, Y);
	std::cout << "���m�O�G" << TheInformation.getDEF() << "  " << "�t�סG" << TheInformation.getSpeed() << "  " << "�ޯ�G" << Abilities[TheInformation.getAbility()];
	Y++;
}

int pokemon::theDamage(int ATK, int DEF, string A, string B)
{
	int x = 0;//�Ĥ@���_�i�ڪ��ݩ�
	int y = 0;//�ĤG���_�i�ڪ��ݩ�

	for (int i = 0; i < 18; i++) {
		if (AllofTypes[i] == A)
			x = i;
		if (AllofTypes[i] == B)
			y = i;
	}
	//�����Y��
	double Coefficient = GetCoefficientofType(x, y);
	//�^�ǥ[���᪺�ˮ`
	return (Coefficient * (ATK - DEF));
}

double pokemon::getCounterAttack(int x)
{
	return 0;
}

void pokemon::Attack(pokemon& m)
{
	int x = rand() % 5 + 1;
	//hitRate��]��0�A�ҥH���D���S��ޯ�A���M�����C
	if (x > m.gethitRate()) {
		int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
		m.setHP(m.getHP() - (TheDamage));
		setHP(getHP() - m.getCounterAttack(TheDamage));
	}
	else
		std::cout << m.getName() << "�j�פF���������C";
}


