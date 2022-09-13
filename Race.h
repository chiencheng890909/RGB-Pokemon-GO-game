#pragma once
#ifndef RACE_H
#define RACE_H
#include <exception>
#include "pokemon.h"
#include "Map.h"

using namespace std;

class NumError :public exception {
public:
	NumError() :exception("�C�������C") {}
};

class Player :public NumError{
private:
	string Name;
	int* Position;
	vector<pokemon*>Pokemons;
	int wins;
public:
	Player();

	//Curator�M��
	Player(string name);

	void changePosition(int i, int j);//�ܧ�D����m��
	void addPokemon(int choice);//�o���_�i�ڡA��iPokemons
	void deletePokemon(int i);//�o���_�i�ڡA���O�_�i�ڼƶq�W�L3��A�R�����w�_�i��
	void showStats(int X, int Y, pokemon& newPokemon);//��ܤw�����_�i�ڡA�æ��A�C
	void showpokemons(int X, int Y);//��ܩҦ��s�����_�i�ڡC

	string GetName();
	pokemon& Getpokemon(int choice);
	int GetNumofPokemons() { return Pokemons.size(); }

	int GetPositionX() { return Position[0]; }
	int GetPositionY() { return Position[1]; }

	int GetWins() { return wins; }
	void SetWins(int x) { wins = x; }
};
template <typename T>
class Race {
private:
	Player thePlayer;
	Map theMap;
	pokemonData AllofPokemon;
	pokemon* Enemy;
	
public:
	Race() { Enemy = nullptr; };
	void Execute();//�C���i��D�{��
	void Moving(T k);//���a����
	void Fight();//�i�D�]�᪺��Եe��
	void Catch(pokemon*& Enemy);//���_�i�ڤ���
	void MeetPokemon();//���v�ʲ����_�i��
};
#endif // !RACE_H

