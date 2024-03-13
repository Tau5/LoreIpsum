#pragma once
#include <list>


class Data
{
private:
	int currentMoney = 0,
		currentCase = 0,
		currentSouls = 0,
		winner = 0;
	std::list<int> drawer;
	std::list<int> maze;  // cleon: "mierda, mierda, mierda"
	std::list<int> defeatedNPCS;
	bool playerWon; // True si la ultima partida ha sido ganado el jugador. False lo contrario.

	enum WINNER {
		NONE,
		TIE,
		PLAYER1,
		PLAYER2
	};

public:

	//------Constructora y destructora:
	Data();
	Data(int mon, int cas, int sou, std::list<int>maz, std::list<int>dra, std::list<int>def);
	~Data();

	//------Setters:
	//----Mazo:
	void AddCardToMaze(int id);
	void SubtractCardFromMaze(int id);
	//----Cajon:
	void AddCardToDrawer(int id);
	void SubtractCardFromDrawer(int id);
	//----NPCs:
	void AddDefeatedNPC(int id);
	//----Dinero:
	void AddMoney(int m);
	void SubtractMoney(int m);
	//----Almas:
	void AddSouls(int s);
	//----Caso:
	void AddCurrentCase();
	//----Ganardor de la ultima partida:
	void setWinner(int i);

	//------Getters:
	//----Mazo:
	const std::list<int> GetMaze(int id) { return maze; }
	//----Cajon:
	const std::list<int> GetDrawer(int id) { return drawer; }
	//----NPCs:
	const std::list<int> GetDefeatedNPC(int id) { return defeatedNPCS; }
	//----Dinero:
	const int GetMoney() { return currentMoney; }
	//----Almas:
	const int GetSouls() { return currentSouls; };
	//----Caso:
	const int GetCurrentCase() { return currentCase; };
	//----Ganador de la ultima partida:
	int getWinner() { return winner; }

	//------Busqueda:
	//----Mazo:
	bool IdIsInMaze(int id);
	//----Cajon:
	bool IdIsInDrawer(int id);
	//----NPCs:
	bool IdIsInDefeatedNPC(int id);

	//------Escritura:
	void Write();
	//------Lectura:
	void Read();

	//------Vaciar:
	void EmptyLists();
	void EmptyMaze();
	void EmptyDrawer();
	void EmptyNPCS();
};