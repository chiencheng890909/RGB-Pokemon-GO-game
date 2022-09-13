#include "Race.h"

Player::Player()
{
	Name = "You";
	Position = new int[2]();
	Position[0] = 20;//x
	Position[1] = 30;//y
	Pokemons.clear();
	wins = 0;
	rlutil::hidecursor();
}

Player::Player(string name)
{
	//�D���ϥ�
	Position = new int[2]();
	Position[0] = -1;//x
	Position[1] = -1;//y
	Pokemons.clear();
	wins = -1;
}

void Player::changePosition(int i, int j)
{
	//�ܧ󪱮a��m
	Position[0] = i;
	Position[1] = j;
}

void Player::addPokemon(int choice)
{
	//�����Ƕi�Ӫ��_�i�ں����÷s�W
	if (choice < 3) {
		Pokemons.push_back(new HealPokemon(choice));
	}
	else if (choice < 6) {
		Pokemons.push_back(new BurningPokemon(choice));
	}
	else if (choice < 9) {
		Pokemons.push_back(new CAPokemon(choice));
	}
	else if (choice < 12) {
		Pokemons.push_back(new ImmunologyPokemon(choice));
	}
	else if (choice < 15) {
		Pokemons.push_back(new LLPokemon(choice));
	}
	else if (choice < 18) {
		Pokemons.push_back(new AvoidPokemon(choice));
	}
	else if (choice < 20) {
		Pokemons.push_back(new pokemon(choice));
	}
	else if (choice < 22) {
		Pokemons.push_back(new DAPokemon(choice));
	}
	else if (choice < 24) {
		Pokemons.push_back(new PoisonPokemon(choice));
	}
	else if (choice < 26) {
		Pokemons.push_back(new LPPokemon(choice));
	}
	else if (choice < 28) {
		Pokemons.push_back(new RSPokemon(choice));
	}
	else if (choice < 31) {
		Pokemons.push_back(new LDPokemon(choice));
	}
	else {
		Pokemons.push_back(new LAPokemon(choice));
	}
}

void Player::deletePokemon(int i)
{
	Pokemons.erase(Pokemons.begin() + i);
}

void Player::showStats(int X, int Y, pokemon& newPokemon)
{
	//�L�X���a�֦����_�i��
	int x = X;
	int y = Y;
	for (int i = 0; i < Pokemons.size(); i++) {
		gotoxy(x, y);
		std::cout << i + 1 << ". " << Pokemons[i]->getName();
		y++;
	}
	
	y = Y + 6;
	gotoxy(x, y);
	std::cout << "�аݱz�O�_�n���A���_�i�ڡH(���\���v��50%)";
	y++;
	gotoxy(x, y);
	std::cout << "0�G���, 1�G���A";
	y++;

	while (true) {
		int Rate = rand() % 2;
		if (kbhit()) {
			char k = getch();
			//�������_�e��
			if (k == '0') {
				if (Rate == 0) {
					gotoxy(x, y);
					std::cout << "�_�i�ڰk�]�F�C";
					y++;
					break;
				}
				gotoxy(x, y);
				std::cout << "�A���������}�F�C";
				y++;
				break;
			}
			//���_�i��
			else if (k == '1') {
				if (Rate == 0) {
					gotoxy(x, y);
					std::cout << "�_�i�ڰk�]�F�C";
					y++;
					break;
				}
				//�p�G���a�w�g�o��3���A��ܩ߱��1 �άO���}
				if (Pokemons.size() == 3) {
					gotoxy(x, y);
					std::cout << "�Щ�ͤ@���_�i��";
					y++;
					while (true) {
						if (kbhit()) {
							char K = getch();
							if (K == '0') {
								gotoxy(x, y);
								std::cout << "�A���������}�F�C";
								y++;
								return;
							}
							else if (K == '1') {
								deletePokemon(K - '1');
								break;
							}
							else if (K == '2') {
								deletePokemon(K - '1');
								break;
							}
							else if (K == '3') {
								deletePokemon(K - '1');
								break;
							}
						}
					}
					gotoxy(x, y);
					std::cout << "�z��ܪ��_�i�ڤw�g�N�a����";
					y++;
				}
				//�s�W�_�i��
				addPokemon(newPokemon.getKind());
				gotoxy(x, y);
				std::cout << newPokemon.getName() << "�����z���٦�C";
				y++;
				break;
			}
		}
	}
	gotoxy(x, y);
	rlutil::anykey("�I�����N��^��a��\n");
}

string Player::GetName()
{
	return Name;
}

void Player::showpokemons(int X,int Y)
{
	for (int i = 0; i < Pokemons.size(); i++) {
		gotoxy(X, Y);
		if (Pokemons[i]->getHP() > 0) {
			cout << (i + 1) << ". " << Pokemons[i]->getName();
			Y++;
		}
	}
}

pokemon& Player::Getpokemon(int choice)
{
	//��W�X�d��A�N��S���_�i�ڥi�H�X�}
	if (choice >= Pokemons.size())
		throw NumError();//�]Exception
	else {
		return *Pokemons[choice];
	}
}
template <typename T>
void Race<T>::Execute()
{

	while (true) {
		T k = T();
		rlutil::hidecursor();
		Moving(k);
		//����7�ӳ��~����While
		if (thePlayer.GetWins() >= 7)
			break;
		MeetPokemon();
		Catch(Enemy);
	}
	rlutil::cls();
	cout << "�𲤧����C" << endl;
	rlutil::msleep(500);
}
template <typename T>
void Race<T>::Moving(T k)
{
	rlutil::cls();
	theMap.printMap();
	while (true) {
		//�I��D�]�X�f�A�}�l�P�D���԰�
		if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '#') {
			Fight();
			rlutil::cls();
			theMap.printMap();
			//����7�ӹD�]�A���a�ӧQ
			if (thePlayer.GetWins() >= 7)
				break;
		}
		//�L�X���a
		rlutil::setColor(4);
		gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY()); std::cout << '@' << std::endl;
		rlutil::resetColor();

		k = rlutil::getkey(); // Get character

		//�Ӫ��a�ҫ�����V�䲾�ʨæL�X������a��m�Ӧ����a�ϲŸ�
		//�A�N���a�L�ܷs���I�A�ýT�w 10% ���v
		if (k == rlutil::KEY_LEFT) {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX() - 1, thePlayer.GetPositionY()))
				thePlayer.changePosition(thePlayer.GetPositionX() - 1, thePlayer.GetPositionY());
		
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
		else if (k == rlutil::KEY_RIGHT) {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX() + 1, thePlayer.GetPositionY()))
				thePlayer.changePosition(thePlayer.GetPositionX() + 1, thePlayer.GetPositionY());
			
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
		else if (k == rlutil::KEY_UP) {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX(), thePlayer.GetPositionY() - 1))
				thePlayer.changePosition(thePlayer.GetPositionX(), thePlayer.GetPositionY() - 1);
			
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
		else if (k == rlutil::KEY_DOWN) {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX(), thePlayer.GetPositionY() + 1))
				thePlayer.changePosition(thePlayer.GetPositionX(), thePlayer.GetPositionY() + 1);
			
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
	}
}
// explicit instantiation declaration
template<> void Race<char>::Moving(char k)
{
	rlutil::cls();
	theMap.printMap();
	while (true) {
		//�I��D�]�X�f�A�}�l�P�D���԰�
		if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '#') {
			Fight();
			rlutil::cls();
			theMap.printMap();
			//����7�ӹD�]�A���a�ӧQ
			if (thePlayer.GetWins() >= 7)
				break;
		}

		//�L�X���a
		rlutil::setColor(4);
		gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY()); std::cout << '@' << std::endl;
		rlutil::resetColor();

		k = rlutil::getkey(); // Get character

		//�Ӫ��a�ҫ�����V�䲾�ʨæL�X������a��m�Ӧ����a�ϲŸ�
		//�A�N���a�L�ܷs���I�A�ýT�w 10% ���v
		if (k == 'a') {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX() - 1, thePlayer.GetPositionY()))
				thePlayer.changePosition(thePlayer.GetPositionX() - 1, thePlayer.GetPositionY());
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
		else if (k == 'd') {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX() + 1, thePlayer.GetPositionY()))
				thePlayer.changePosition(thePlayer.GetPositionX() + 1, thePlayer.GetPositionY());
			
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
		else if (k == 'w') {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX(), thePlayer.GetPositionY() - 1))
				thePlayer.changePosition(thePlayer.GetPositionX(), thePlayer.GetPositionY() - 1);
		
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
		else if (k == 's') {
			gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY());
			if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == ';')
				rlutil::setColor(10);
			else if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '~')
				rlutil::setColor(9);
			std::cout << theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) << std::endl;
			rlutil::resetColor();

			if (theMap.check(thePlayer.GetPositionX(), thePlayer.GetPositionY() + 1))
				thePlayer.changePosition(thePlayer.GetPositionX(), thePlayer.GetPositionY() + 1);
		
			int x = rand() % 10 + 1;
			if (x == 1)
				return;
		}
	}
}
template <typename T>
void Race<T>::Fight()
{
	//�إ߹D��
	Player Enemy("curator");
	for (int i = 0; i < 3; i++) {
		int Z = rand() % 32;
		Enemy.addPokemon(Z);
	}
	//���a�P�D�����_�i�ڥX���Ƨ�
	int Left = 0;
	int Right = 0;

	pokemon* it1;
	pokemon* it2;
	//�������a�Ĥ@���X���_�i�ڡA�p�G�S���N�]Catch�õ������
	try {
		it1 = &thePlayer.Getpokemon(Left);
	}
	catch (Player::NumError& e) {
		std::cout << e.what();
		return;
	}

	it2 = &Enemy.Getpokemon(Right);

	rlutil::cls();

	//�L�X��Ԥ��e
	it1->PrintIcon(5, 2);
	thePlayer.showpokemons(20, 30);
	it1->PrintInformation(20, 35);
	it2->PrintIcon(50, 2);
	Enemy.showpokemons(65, 30);
	it2->PrintInformation(65, 35);

	//�԰���T�L�X��X,Y��m
	int X = 45;
	int Y = 40;
	int Z = 41;

	while (true) {
		rlutil::hidecursor();
		if (kbhit()) {
			char k = getch();
			if (k == ' ') {
				//����t�סA�t�װ����u��
				if (it1->getSpeed() >= it2->getSpeed()) {
					gotoxy(X, Y);
					for (int i = 0; i < 100; i++)
						std::cout << " ";
					gotoxy(X, Y);

					it1->Attack(*it2);
					//�������n��s���
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					//�_�i�ڦ��`���U�@���_�i��
					if (it2->getHP() <= 0) {
						gotoxy(X, Y);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Y);
						std::cout << it2->getName() << "�}�`�C";
						Right++;
						//���_�i�ڡA�p�G�S���N��D���ԱѡA�������
						try {
							it2 = &Enemy.Getpokemon(Right);
						}
						catch (Player::NumError& e) {
							gotoxy(X, Y + 3);
							std::cout << e.what();
							break;
						}

						gotoxy(X, Z);//
						for (int i = 0; i < 100; i++)//
							std::cout << " ";//
						gotoxy(X, Z);//

						gotoxy(X, Y + 2);
						rlutil::anykey("�I�����N���~��\n");
						rlutil::cls();
						//��s�������
						it1->PrintIcon(5, 2);
						thePlayer.showpokemons(20, 30);
						it1->PrintInformation(20, 35);
						it2->PrintIcon(50, 2);
						Enemy.showpokemons(65, 30);
						it2->PrintInformation(65, 35);
						continue;
					}
					gotoxy(X, Z);
					it2->Attack(*it1);
					//�������n��s���
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					//�_�i�ڦ��`���U�@���_�i��
					if (it1->getHP() <= 0) {
						gotoxy(X, Z);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Z);
						std::cout << it1->getName() << "�}�`�C";
						Left++;
						//���_�i�ڡA�p�G�S���N���a�ԱѡA�������
						try {
							it1 = &thePlayer.Getpokemon(Left);
						}
						catch (Player::NumError& e) {
							gotoxy(X, Y + 3);
							std::cout << e.what();
							break;
						}

						gotoxy(X, Y);//
						for (int i = 0; i < 100; i++)//
							std::cout << " ";//
						gotoxy(X, Y);//

						gotoxy(X, Y + 2);
						rlutil::anykey("�I�����N���~��\n");
						rlutil::cls();
						//��s�������
						it1->PrintIcon(5, 2);
						thePlayer.showpokemons(20, 30);
						it1->PrintInformation(20, 35);
						it2->PrintIcon(50, 2);
						Enemy.showpokemons(65, 30);
						it2->PrintInformation(65, 35);
						continue;
					}
				}
				else {
					gotoxy(X, Y);
					for (int i = 0; i < 100; i++)
						std::cout << " ";
					gotoxy(X, Y);

					it2->Attack(*it1);
					//�������n��s���
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					//�_�i�ڦ��`���U�@���_�i��
					if (it1->getHP() <= 0) {
						gotoxy(X, Y);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Y);
						std::cout << it1->getName() << "�}�`�C";
						Left++;
						//���_�i�ڡA�p�G�S���N���a�ԱѡA�������
						try {
							it1 = &thePlayer.Getpokemon(Left);
						}
						catch (Player::NumError& e) {
							gotoxy(X, Y + 3);
							std::cout << e.what();
							break;
						}
						gotoxy(X, Y + 2);
						rlutil::anykey("�I�����N���~��\n");
						rlutil::cls();
						//��s�������
						it1->PrintIcon(5, 2);
						thePlayer.showpokemons(20, 30);
						it1->PrintInformation(20, 35);
						it2->PrintIcon(50, 2);
						Enemy.showpokemons(65, 30);
						it2->PrintInformation(65, 35);
						continue;
					}
					gotoxy(X, Z);
					it1->Attack(*it2);
					//�������n��s���
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					if (it2->getHP() <= 0) {
						gotoxy(X, Z);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Z);
						std::cout << it2->getName() << "�}�`�C";
						Right++;
						//���_�i�ڡA�p�G�S���N��D���ԱѡA�������
						try {
							it2 = &Enemy.Getpokemon(Right);
						}
						catch (Player::NumError& e) {
							gotoxy(X, Y + 3);
							std::cout << e.what();
							break;
						}
						gotoxy(X, Y + 2);
						rlutil::anykey("�I�����N���~��\n");
						rlutil::cls();
						//��s�������
						it1->PrintIcon(5, 2);
						thePlayer.showpokemons(20, 30);
						it1->PrintInformation(20, 35);
						it2->PrintIcon(50, 2);
						Enemy.showpokemons(65, 30);
						it2->PrintInformation(65, 35);
						continue;
					}
				}
				std::cout.flush();
			}
		}
	}
	gotoxy(X, Y + 4);
	if (thePlayer.Getpokemon(thePlayer.GetNumofPokemons()-1).getHP() > 0) {
		thePlayer.SetWins(thePlayer.GetWins() + 1);
		std::cout << "���ߧA�D�Ԧ��\�A ";
		theMap.SetMap(thePlayer.GetPositionX(), thePlayer.GetPositionY(), 'X');
	}	
	else {
		std::cout << "�A���A�F�A ";
	}
	for (int i = 0; i < thePlayer.GetNumofPokemons(); i++) {
		int K = thePlayer.Getpokemon(0).getKind();
		thePlayer.deletePokemon(0);
		thePlayer.addPokemon(K);
	}
	rlutil::anykey("�I�����N��^��a��\n");
}
template <typename T>
void Race<T>::Catch(pokemon*& Enemy)
{
	rlutil::cls();
	gotoxy(50, 30);

	std::cout << "�J�쳥���_�i�ڡI�I�I" << endl;
	rlutil::msleep(500);
	//�L�X�_�i�ڸ�ƻP�������
	Enemy->PrintIcon(5,2);
	Enemy->PrintInformation (50, 6);
	thePlayer.showStats(50, 15, *Enemy);
}
template <typename T>
void Race<T>::MeetPokemon()
{
	if (Enemy != nullptr)
		delete Enemy;
	//�H�����ͤ@���_�i��
	int x = rand() % 32;
	char P = theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY());
	if (P == ';') {
		x = rand() % 10 + 1;
		if (x < 5) {
			x = rand() % 3;
			Enemy = new HealPokemon(x);
			return;
		}
		x = rand() % 32;
	}
	else if (P == '~') {
		x = rand() % 10 + 1;
		if (x < 5) {
			x = rand() % 3 + 6;
			Enemy = new CAPokemon(x);
			return;
		}
		x = rand() % 32;
	}
	if (x < 3) {
		Enemy = new HealPokemon(x);
	}
	else if (x < 6) {
		Enemy = new BurningPokemon(x);
	}
	else if (x < 9) {
		Enemy = new CAPokemon(x);
	}
	else if (x < 12) {
		Enemy = new ImmunologyPokemon(x);
	}
	else if (x < 15) {
		Enemy = new LLPokemon(x);
	}
	else if (x < 18) {
		Enemy = new AvoidPokemon(x);
	}
	else if (x < 20) {
		Enemy = new pokemon(x);
	}
	else if (x < 22) {
		Enemy = new DAPokemon(x);
	}
	else if (x < 24) {
		Enemy = new PoisonPokemon(x);
	}
	else if (x < 26) {
		Enemy = new LPPokemon(x);
	}
	else if (x < 28) {
		Enemy = new RSPokemon(x);
	}
	else if (x < 31) {
		Enemy = new LDPokemon(x);
	}
	else {
		Enemy = new LAPokemon(x);
	}
}

template class Race <char>;
template class Race <int>;
