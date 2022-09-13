#pragma once
#ifndef POKEMON_H
#define POKEMON_H

#include<vector>
#include<string>
#include<stdlib.h>
#include<time.h>
#include "rlutil.h"

using namespace std;

//寶可夢基本設定
class Information {
private:
	string Name;
	string Type;
	int HP;
	int MaxHP;
	int ATK;
	int DEF;
	int Speed;
	int Ability;
public:
	Information(string theName, string theType, int TheHP, int TheATK, int TheDEF, int TheSpeed, int TheAbility)
		:Name(theName), Type(theType), HP(TheHP), MaxHP(TheHP) , ATK(TheATK), DEF(TheDEF), Speed(TheSpeed), Ability(TheAbility) {}
	string getName() { return Name; }
	string getType() { return Type; }
	int getHP() { return HP; }
	int getMaxHP() const { return MaxHP; }
	void setHP(int TheHP) { HP = TheHP; }

	int getATK() { return ATK; }
	void setATK(int TheATK) { ATK = TheATK; }

	int getDEF() { return DEF; }
	void setDEF(int TheDEF) { DEF = TheDEF; }

	int getSpeed() { return Speed; }
	void setSpeed(int TheSpeed) { Speed = TheSpeed; }

	int getAbility() { return Ability; }
};
//寶可夢圖案
class Icon {
private:
	vector<int> Sets;//放置設定
	string TheWords;//放置輸出文字
public:
	Icon(string Input);//傳入字串 分析成設定與輸出字元

	int GetSets(int i) { return Sets[i]; }
	int GetSize() { return Sets.size(); }
	string GetTheWords() { return TheWords; }
};

class pokemonData {
private:
	vector<vector<Icon>>Icons;//所有寶可夢的圖像
	vector<Information>Informations;//所有寶可夢的設定
	vector<vector<double>> Types;//屬性相剋表

	void ReadIcons();
	void ReadInformations();
	void ReadTypes();

public:
	pokemonData();//讀入所有的寶可夢資料

	double GetCoefficientofType(int i, int j);//對屬性相剋表，回傳相對應的數字

	vector<Icon> GetIcon(int choice);
	Information GetInformation(int choice);
};
//此處用繼承只是為了方便提取資料
class pokemon :public pokemonData {
private:
	vector<Icon> TheIcon;
	Information TheInformation;
	bool Debuff;
	int hitRate;
	int Kind;
public:
	//從pokemonData直接拿取資料
	pokemon(int choice) :TheIcon(GetIcon(choice)), TheInformation(GetInformation(choice)), 
		Debuff(false), hitRate(0),Kind(choice) {};

	void PrintIcon(int x,int y);//印出pokemon的圖案
	void PrintInformation(int X, int Y);//印出pokemon的資料
	
	int theDamage(int ATK, int DEF, string A, string B);//計算造成傷害

	int getKind() { return Kind; }

	vector<Icon> getIcon() { return TheIcon; }
	Information getInformation() { return TheInformation; }

	string getName() { return TheInformation.getName(); }
	string getType() { return TheInformation.getType(); }

	int getHP() { return TheInformation.getHP(); }
	int getMaxHP() { return TheInformation.getMaxHP(); }
	void setHP(int TheHP) { TheInformation.setHP(TheHP); }

	int getATK() { return TheInformation.getATK(); }
	void setATK(int TheATK) { TheInformation.setATK(TheATK); }

	virtual int getDEF() { return TheInformation.getDEF(); }
	void setDEF(int TheDEF) { TheInformation.setDEF(TheDEF); }

	int getSpeed() { return TheInformation.getSpeed(); }
	void setSpeed(int TheSpeed) { TheInformation.setSpeed(TheSpeed); }

	int getAbility() { return TheInformation.getAbility(); }

	int getDebuff() { return Debuff; }
	void setDebuff(bool x) { Debuff = x; }

	double gethitRate() { return hitRate; }
	void sethitRate(int x) { hitRate = x; }

	void showStats() { cout << getName() << ": " << getHP() << "/" << getMaxHP() << endl; }
	
	virtual double getCounterAttack(int x);
	virtual void Attack(pokemon& m);
};
//1.Heal
class HealPokemon : public pokemon
{
private:
public:
	HealPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			setHP(getHP() + 3);
			cout << getName() << "治癒了自己。"<<"  ";
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
//2.Burning
class BurningPokemon : public pokemon
{
private:
public:
	BurningPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			x = rand() % 3 + 1;
			int TheDamage = theDamage(getATK(), m.getDEF(),getType(),m.getType()) + x;
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			cout << m.getName() << "受到燒傷，扣除血量" << x << "  ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
//3.Counter Attack
class CAPokemon : public pokemon
{
private:
public:
	CAPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
	double getCounterAttack(int x) { return x * 0.2; }
};
//4.Immunology
class ImmunologyPokemon : public pokemon
{
private:
public:
	ImmunologyPokemon(int choice) :pokemon(choice) { setDebuff(true); }
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = getATK() - m.getDEF();
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
//5.Leech Life
class LLPokemon : public pokemon
{
private:
public:
	LLPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int x = rand() % 2 + 1;
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊"<<"  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			cout << getName() << "吸收了" << x << "點血量" << "  ";
			setHP(getHP() + x);
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
//6.Avoid
class AvoidPokemon : public pokemon
{
private:
public:
	AvoidPokemon(int choice) :pokemon(choice) { sethitRate(1); }
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
//7.Double Attack
class DAPokemon : public pokemon
{
private:
public:
	DAPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			m.setHP(m.getHP() - (TheDamage));
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));

			if (x == 1) {
				cout << getName() << "再次發動攻擊。" << "  ";
				int TheDamage = getATK() - m.getDEF();
				cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
				m.setHP(m.getHP() - (TheDamage));
				if (m.getCounterAttack(TheDamage) > 0)
					cout << getName() << "受到反擊" << "  ";
				setHP(getHP() - m.getCounterAttack(TheDamage));
			}
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
//8.Poison
class PoisonPokemon : public pokemon
{
private:
	int Times;
public:
	PoisonPokemon(int choice) :pokemon(choice) { Times = -1; }
	void Attack(pokemon& m) {

		srand(time(NULL));
		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			if (m.getHP() < 0)
				Times = -1;

			if (Times == -1)
				Times = 2;
			else if (Times > 0) {
				m.setHP(m.getHP() - 2);
				cout << m.getName() << "中毒了，血量-2。"<<"  ";
				Times--;
			}
		}
		else
			cout << m.getName() << "迴避了本次攻擊。";
	}
};
//9.Lower Speed
class LPPokemon : public pokemon
{
private:
	int Times;
public:
	LPPokemon(int choice) :pokemon(choice) { Times = -1; }
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			
			if (m.getHP() < 0)
				Times = -1;
			
			if (!m.getDebuff()) {

				if (Times == -1) {
					Times = 2;
					cout << getName() << "發動技能。" << "  ";
				}
					
				else if (Times > 0) {
					m.setSpeed(m.getSpeed() - 2);
					Times--;
					cout << m.getName() << "受到驚嚇，速度-2" << "  ";
				}
			}
		}
		else
			cout << m.getName() << "迴避了本次攻擊" << "  ";
	}
};
//10.Rock Skin
class RSPokemon : public pokemon
{
private:
public:
	RSPokemon(int choice) :pokemon(choice) {}

	int getDEF() { return getInformation().getDEF() + 2; }

	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "迴避了本次攻擊。";
	}
};
//11.Lower Defence
class LDPokemon : public pokemon
{
private:
	int Times;
public:
	LDPokemon(int choice) :pokemon(choice) { Times = -1; }

	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";

			setHP(getHP() - m.getCounterAttack(TheDamage));
			if (m.getHP() < 0)
				Times = -1;
			if (!m.getDebuff()) {
				if (Times == -1) {
					Times = 2;
					cout << getName() << "發動技能" << "  ";
				}
					
				else if (Times > 0) {
					cout << m.getName() << "中毒了，防禦-2" << "  ";
					m.setDEF(m.getDEF() - 2);
					Times--;
				}
			}
			else
				cout << m.getName() << "免疫了中毒效果" << "  ";
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
//12.Lower Attack
class LAPokemon : public pokemon
{
private:
	int Times;
public:
	LAPokemon(int choice) :pokemon(choice) { Times = -1; }

	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//產生1~5
		//X與敵人的迴避值比較 初設為0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "對" << m.getName() << "造成" << TheDamage << "傷害" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "受到反擊" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			if (m.getHP() < 0)
				Times = -1;
			if (!m.getDebuff()) {
				if (Times == -1) {
					Times = 2;
					cout << getName() << "發動技能" << "  ";
				}
				else if (Times > 0) {
					cout << m.getName() << "中毒了，攻擊-2" << "  ";
					m.setATK(m.getATK() - 2);
					Times--;
				}
			}
			else
				cout << m.getName() << "免疫了中毒效果。" << "  ";
		}
		else
			cout << m.getName() << "迴避了本次攻擊。" << "  ";
	}
};
#endif // POKEMON_H

