#pragma once
#ifndef POKEMON_H
#define POKEMON_H

#include<vector>
#include<string>
#include<stdlib.h>
#include<time.h>
#include "rlutil.h"

using namespace std;

//�_�i�ڰ򥻳]�w
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
//�_�i�ڹϮ�
class Icon {
private:
	vector<int> Sets;//��m�]�w
	string TheWords;//��m��X��r
public:
	Icon(string Input);//�ǤJ�r�� ���R���]�w�P��X�r��

	int GetSets(int i) { return Sets[i]; }
	int GetSize() { return Sets.size(); }
	string GetTheWords() { return TheWords; }
};

class pokemonData {
private:
	vector<vector<Icon>>Icons;//�Ҧ��_�i�ڪ��Ϲ�
	vector<Information>Informations;//�Ҧ��_�i�ڪ��]�w
	vector<vector<double>> Types;//�ݩʬ۫g��

	void ReadIcons();
	void ReadInformations();
	void ReadTypes();

public:
	pokemonData();//Ū�J�Ҧ����_�i�ڸ��

	double GetCoefficientofType(int i, int j);//���ݩʬ۫g��A�^�Ǭ۹������Ʀr

	vector<Icon> GetIcon(int choice);
	Information GetInformation(int choice);
};
//���B���~�ӥu�O���F��K�������
class pokemon :public pokemonData {
private:
	vector<Icon> TheIcon;
	Information TheInformation;
	bool Debuff;
	int hitRate;
	int Kind;
public:
	//�qpokemonData�����������
	pokemon(int choice) :TheIcon(GetIcon(choice)), TheInformation(GetInformation(choice)), 
		Debuff(false), hitRate(0),Kind(choice) {};

	void PrintIcon(int x,int y);//�L�Xpokemon���Ϯ�
	void PrintInformation(int X, int Y);//�L�Xpokemon�����
	
	int theDamage(int ATK, int DEF, string A, string B);//�p��y���ˮ`

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

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			setHP(getHP() + 3);
			cout << getName() << "�v¡�F�ۤv�C"<<"  ";
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
	}
};
//2.Burning
class BurningPokemon : public pokemon
{
private:
public:
	BurningPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			x = rand() % 3 + 1;
			int TheDamage = theDamage(getATK(), m.getDEF(),getType(),m.getType()) + x;
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			cout << m.getName() << "����N�ˡA������q" << x << "  ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
	}
};
//3.Counter Attack
class CAPokemon : public pokemon
{
private:
public:
	CAPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
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

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = getATK() - m.getDEF();
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
	}
};
//5.Leech Life
class LLPokemon : public pokemon
{
private:
public:
	LLPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int x = rand() % 2 + 1;
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������"<<"  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			cout << getName() << "�l���F" << x << "�I��q" << "  ";
			setHP(getHP() + x);
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
	}
};
//6.Avoid
class AvoidPokemon : public pokemon
{
private:
public:
	AvoidPokemon(int choice) :pokemon(choice) { sethitRate(1); }
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
	}
};
//7.Double Attack
class DAPokemon : public pokemon
{
private:
public:
	DAPokemon(int choice) :pokemon(choice) {}
	void Attack(pokemon& m) {

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			m.setHP(m.getHP() - (TheDamage));
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));

			if (x == 1) {
				cout << getName() << "�A���o�ʧ����C" << "  ";
				int TheDamage = getATK() - m.getDEF();
				cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
				m.setHP(m.getHP() - (TheDamage));
				if (m.getCounterAttack(TheDamage) > 0)
					cout << getName() << "�������" << "  ";
				setHP(getHP() - m.getCounterAttack(TheDamage));
			}
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
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
		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			if (m.getHP() < 0)
				Times = -1;

			if (Times == -1)
				Times = 2;
			else if (Times > 0) {
				m.setHP(m.getHP() - 2);
				cout << m.getName() << "���r�F�A��q-2�C"<<"  ";
				Times--;
			}
		}
		else
			cout << m.getName() << "�j�פF���������C";
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

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			
			if (m.getHP() < 0)
				Times = -1;
			
			if (!m.getDebuff()) {

				if (Times == -1) {
					Times = 2;
					cout << getName() << "�o�ʧޯ�C" << "  ";
				}
					
				else if (Times > 0) {
					m.setSpeed(m.getSpeed() - 2);
					Times--;
					cout << m.getName() << "�������~�A�t��-2" << "  ";
				}
			}
		}
		else
			cout << m.getName() << "�j�פF��������" << "  ";
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

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
		}
		else
			cout << m.getName() << "�j�פF���������C";
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

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";

			setHP(getHP() - m.getCounterAttack(TheDamage));
			if (m.getHP() < 0)
				Times = -1;
			if (!m.getDebuff()) {
				if (Times == -1) {
					Times = 2;
					cout << getName() << "�o�ʧޯ�" << "  ";
				}
					
				else if (Times > 0) {
					cout << m.getName() << "���r�F�A���m-2" << "  ";
					m.setDEF(m.getDEF() - 2);
					Times--;
				}
			}
			else
				cout << m.getName() << "�K�̤F���r�ĪG" << "  ";
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
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

		int x = rand() % 5 + 1;//����1~5
		//X�P�ĤH���j�׭Ȥ�� ��]��0
		if (x > m.gethitRate()) {
			int TheDamage = theDamage(getATK(), m.getDEF(), getType(), m.getType());
			cout << getName() << "��" << m.getName() << "�y��" << TheDamage << "�ˮ`" << " ";
			m.setHP(m.getHP() - (TheDamage));
			if (m.getCounterAttack(TheDamage) > 0)
				cout << getName() << "�������" << "  ";
			setHP(getHP() - m.getCounterAttack(TheDamage));
			if (m.getHP() < 0)
				Times = -1;
			if (!m.getDebuff()) {
				if (Times == -1) {
					Times = 2;
					cout << getName() << "�o�ʧޯ�" << "  ";
				}
				else if (Times > 0) {
					cout << m.getName() << "���r�F�A����-2" << "  ";
					m.setATK(m.getATK() - 2);
					Times--;
				}
			}
			else
				cout << m.getName() << "�K�̤F���r�ĪG�C" << "  ";
		}
		else
			cout << m.getName() << "�j�פF���������C" << "  ";
	}
};
#endif // POKEMON_H

