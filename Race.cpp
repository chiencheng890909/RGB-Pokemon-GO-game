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
	//道長使用
	Position = new int[2]();
	Position[0] = -1;//x
	Position[1] = -1;//y
	Pokemons.clear();
	wins = -1;
}

void Player::changePosition(int i, int j)
{
	//變更玩家位置
	Position[0] = i;
	Position[1] = j;
}

void Player::addPokemon(int choice)
{
	//偵測傳進來的寶可夢種類並新增
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
	//印出玩家擁有的寶可夢
	int x = X;
	int y = Y;
	for (int i = 0; i < Pokemons.size(); i++) {
		gotoxy(x, y);
		std::cout << i + 1 << ". " << Pokemons[i]->getName();
		y++;
	}
	
	y = Y + 6;
	gotoxy(x, y);
	std::cout << "請問您是否要收服此寶可夢？(成功機率為50%)";
	y++;
	gotoxy(x, y);
	std::cout << "0：放棄, 1：收服";
	y++;

	while (true) {
		int Rate = rand() % 2;
		if (kbhit()) {
			char k = getch();
			//結束抓寶畫面
			if (k == '0') {
				if (Rate == 0) {
					gotoxy(x, y);
					std::cout << "寶可夢逃跑了。";
					y++;
					break;
				}
				gotoxy(x, y);
				std::cout << "你悄悄的離開了。";
				y++;
				break;
			}
			//抓寶可夢
			else if (k == '1') {
				if (Rate == 0) {
					gotoxy(x, y);
					std::cout << "寶可夢逃跑了。";
					y++;
					break;
				}
				//如果玩家已經得到3隻，選擇拋棄其1 或是離開
				if (Pokemons.size() == 3) {
					gotoxy(x, y);
					std::cout << "請放生一隻寶可夢";
					y++;
					while (true) {
						if (kbhit()) {
							char K = getch();
							if (K == '0') {
								gotoxy(x, y);
								std::cout << "你悄悄的離開了。";
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
					std::cout << "您選擇的寶可夢已經就地野放";
					y++;
				}
				//新增寶可夢
				addPokemon(newPokemon.getKind());
				gotoxy(x, y);
				std::cout << newPokemon.getName() << "成為您的夥伴。";
				y++;
				break;
			}
		}
	}
	gotoxy(x, y);
	rlutil::anykey("點擊任意鍵回到地圖\n");
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
	//當超出範圍，代表沒有寶可夢可以出陣
	if (choice >= Pokemons.size())
		throw NumError();//跑Exception
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
		//直到7勝場才停止While
		if (thePlayer.GetWins() >= 7)
			break;
		MeetPokemon();
		Catch(Enemy);
	}
	rlutil::cls();
	cout << "攻略完成。" << endl;
	rlutil::msleep(500);
}
template <typename T>
void Race<T>::Moving(T k)
{
	rlutil::cls();
	theMap.printMap();
	while (true) {
		//碰到道館出口，開始與道長戰鬥
		if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '#') {
			Fight();
			rlutil::cls();
			theMap.printMap();
			//佔領7個道館，玩家勝利
			if (thePlayer.GetWins() >= 7)
				break;
		}
		//印出玩家
		rlutil::setColor(4);
		gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY()); std::cout << '@' << std::endl;
		rlutil::resetColor();

		k = rlutil::getkey(); // Get character

		//照玩家所按的方向鍵移動並印出原先玩家位置該有的地圖符號
		//再將玩家印至新的點，並確定 10% 機率
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
		//碰到道館出口，開始與道長戰鬥
		if (theMap.GetAttributes(thePlayer.GetPositionX(), thePlayer.GetPositionY()) == '#') {
			Fight();
			rlutil::cls();
			theMap.printMap();
			//佔領7個道館，玩家勝利
			if (thePlayer.GetWins() >= 7)
				break;
		}

		//印出玩家
		rlutil::setColor(4);
		gotoxy(thePlayer.GetPositionX(), thePlayer.GetPositionY()); std::cout << '@' << std::endl;
		rlutil::resetColor();

		k = rlutil::getkey(); // Get character

		//照玩家所按的方向鍵移動並印出原先玩家位置該有的地圖符號
		//再將玩家印至新的點，並確定 10% 機率
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
	//建立道長
	Player Enemy("curator");
	for (int i = 0; i < 3; i++) {
		int Z = rand() % 32;
		Enemy.addPokemon(Z);
	}
	//玩家與道長的寶可夢出場排序
	int Left = 0;
	int Right = 0;

	pokemon* it1;
	pokemon* it2;
	//拿取玩家第一隻出戰寶可夢，如果沒抓到就跑Catch並結束對戰
	try {
		it1 = &thePlayer.Getpokemon(Left);
	}
	catch (Player::NumError& e) {
		std::cout << e.what();
		return;
	}

	it2 = &Enemy.Getpokemon(Right);

	rlutil::cls();

	//印出對戰內容
	it1->PrintIcon(5, 2);
	thePlayer.showpokemons(20, 30);
	it1->PrintInformation(20, 35);
	it2->PrintIcon(50, 2);
	Enemy.showpokemons(65, 30);
	it2->PrintInformation(65, 35);

	//戰鬥資訊印出的X,Y位置
	int X = 45;
	int Y = 40;
	int Z = 41;

	while (true) {
		rlutil::hidecursor();
		if (kbhit()) {
			char k = getch();
			if (k == ' ') {
				//比較速度，速度高的優先
				if (it1->getSpeed() >= it2->getSpeed()) {
					gotoxy(X, Y);
					for (int i = 0; i < 100; i++)
						std::cout << " ";
					gotoxy(X, Y);

					it1->Attack(*it2);
					//攻擊完要刷新資料
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					//寶可夢死亡換下一隻寶可夢
					if (it2->getHP() <= 0) {
						gotoxy(X, Y);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Y);
						std::cout << it2->getName() << "陣亡。";
						Right++;
						//換寶可夢，如果沒抓到代表道長戰敗，結束對戰
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
						rlutil::anykey("點擊任意鍵繼續\n");
						rlutil::cls();
						//刷新全部資料
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
					//攻擊完要刷新資料
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					//寶可夢死亡換下一隻寶可夢
					if (it1->getHP() <= 0) {
						gotoxy(X, Z);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Z);
						std::cout << it1->getName() << "陣亡。";
						Left++;
						//換寶可夢，如果沒抓到代表玩家戰敗，結束對戰
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
						rlutil::anykey("點擊任意鍵繼續\n");
						rlutil::cls();
						//刷新全部資料
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
					//攻擊完要刷新資料
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					//寶可夢死亡換下一隻寶可夢
					if (it1->getHP() <= 0) {
						gotoxy(X, Y);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Y);
						std::cout << it1->getName() << "陣亡。";
						Left++;
						//換寶可夢，如果沒抓到代表玩家戰敗，結束對戰
						try {
							it1 = &thePlayer.Getpokemon(Left);
						}
						catch (Player::NumError& e) {
							gotoxy(X, Y + 3);
							std::cout << e.what();
							break;
						}
						gotoxy(X, Y + 2);
						rlutil::anykey("點擊任意鍵繼續\n");
						rlutil::cls();
						//刷新全部資料
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
					//攻擊完要刷新資料
					thePlayer.showpokemons(20, 30);
					it1->PrintInformation(20, 35);
					Enemy.showpokemons(65, 30);
					it2->PrintInformation(65, 35);
					if (it2->getHP() <= 0) {
						gotoxy(X, Z);
						for (int i = 0; i < 100; i++)
							std::cout << " ";
						gotoxy(X, Z);
						std::cout << it2->getName() << "陣亡。";
						Right++;
						//換寶可夢，如果沒抓到代表道長戰敗，結束對戰
						try {
							it2 = &Enemy.Getpokemon(Right);
						}
						catch (Player::NumError& e) {
							gotoxy(X, Y + 3);
							std::cout << e.what();
							break;
						}
						gotoxy(X, Y + 2);
						rlutil::anykey("點擊任意鍵繼續\n");
						rlutil::cls();
						//刷新全部資料
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
		std::cout << "恭喜你挑戰成功， ";
		theMap.SetMap(thePlayer.GetPositionX(), thePlayer.GetPositionY(), 'X');
	}	
	else {
		std::cout << "再接再厲， ";
	}
	for (int i = 0; i < thePlayer.GetNumofPokemons(); i++) {
		int K = thePlayer.Getpokemon(0).getKind();
		thePlayer.deletePokemon(0);
		thePlayer.addPokemon(K);
	}
	rlutil::anykey("點擊任意鍵回到地圖\n");
}
template <typename T>
void Race<T>::Catch(pokemon*& Enemy)
{
	rlutil::cls();
	gotoxy(50, 30);

	std::cout << "遇到野生寶可夢！！！" << endl;
	rlutil::msleep(500);
	//印出寶可夢資料與抓取介面
	Enemy->PrintIcon(5,2);
	Enemy->PrintInformation (50, 6);
	thePlayer.showStats(50, 15, *Enemy);
}
template <typename T>
void Race<T>::MeetPokemon()
{
	if (Enemy != nullptr)
		delete Enemy;
	//隨機產生一隻寶可夢
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
