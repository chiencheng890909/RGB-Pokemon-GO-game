#pragma once
#ifndef RACE_H
#define RACE_H
#include <exception>
#include "pokemon.h"
#include "Map.h"

using namespace std;

class NumError :public exception {
public:
	NumError() :exception("遊戲結束。") {}
};

class Player :public NumError{
private:
	string Name;
	int* Position;
	vector<pokemon*>Pokemons;
	int wins;
public:
	Player();

	//Curator專用
	Player(string name);

	void changePosition(int i, int j);//變更主角位置用
	void addPokemon(int choice);//得到寶可夢，放進Pokemons
	void deletePokemon(int i);//得到寶可夢，但是寶可夢數量超過3位，刪除指定寶可夢
	void showStats(int X, int Y, pokemon& newPokemon);//顯示已有的寶可夢，並收服。
	void showpokemons(int X, int Y);//顯示所有存活的寶可夢。

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
	void Execute();//遊戲進行主程式
	void Moving(T k);//操縱角色
	void Fight();//進道館後的對戰畫面
	void Catch(pokemon*& Enemy);//抓寶可夢介面
	void MeetPokemon();//機率性產生寶可夢
};
#endif // !RACE_H

