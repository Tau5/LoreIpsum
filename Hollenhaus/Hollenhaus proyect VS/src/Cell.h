#pragma once
#include <vector>
#include "game/Card.h"
#include <functional>
#include "game/Component.h"

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void()>;

constexpr int ADJACENTS = 4 + 1; // direcciones posibles + direccion nula

namespace CellData {

enum Owner
{
	NONE,
	PLAYER1,
	PLAYER2,
	NULO
};

enum Direction
{
	Up,
	Right,
	Down,
	Left,
	None
};

}

class Cell :public ComponentUpdate
{
	bool active; // si en la celda se pueden jugar cartas o no
	bool corner; // si la celda es esquina de tablero o no
	bool center; // si la celda es centro de trablero o no
	int totalValue; // puntuacion con los efectos aplicados
	CellData::Owner player; // a que jugador pertenece
	Card* card; // carta posicionada en esta celda
	std::array<Cell*, ADJACENTS> adjacents; // punteros a las celdas adyacentes en cruz (arriba, abajo, izq, der)
	std::list<SDLEventCallback> effectCallbacks; // lista de los efectos que tiene una celda concreta
	std::list<SDLEventCallback>::iterator listIT;

	void emit() const;

public:
	Cell();
	Cell(Cell& cell); // ctor. por copia
	Cell(Card* card, CellData::Owner);
	~Cell();

	void addEffect(SDLEventCallback effectCallback);
	void applyValue(Card* card);
	void addTotal(int add);
	void cleanEffectList();

	// getters
	CellData::Owner getOwner() { return player; }
	bool getActive() const		{ return active; }
	bool getCorner() const		{ return corner; }
	bool getCenter() const		{ return center; }
	int getTotalValue() const	{ return totalValue; }
	CellData::Owner getPlayer() const		{ return player; }
	Card* getCard() const		{ return card; }
	std::array<Cell*, ADJACENTS>& getAdjacents() { return adjacents; } // sets pointers to adjacent
	std::list<SDLEventCallback>& getEffects() { return effectCallbacks; }

	// setters
	void setActive(bool v)		{ active = v; }
	void setCorner(bool v)		{ corner = v; }
	void setCenter(bool v)		{ center = v; }
	void setTotalValue(int v)	{ totalValue = v;}
	void setPlayer(CellData::Owner o)		{ player = o; }
	void setCard(Card* c, CellData::Owner o);
	void deleteCard() const		{ delete card; } // ???
	void setAdjacents(std::array<Cell*, ADJACENTS>& a) { adjacents = a; }
	void blockEffects(Cell* c);

	Cell& operator=(const Cell& o)
	{
		// delete current list in data;
		// deep copy o.data to data here;
		return *this;
	}
};