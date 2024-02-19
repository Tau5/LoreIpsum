#pragma once
#include "Card.h"
#include "Cell.h"
#include "game/Board.h"

class EffectCollection
{
private:
	Card* card;
	Board* board;
	Cell* cell;


public:
	// ---- TIPOS DE EFECTOS ----
	// a�ade valor a algunas o todas sus adyacentes
	void addValueAdj(enum Direction, int add, bool ultimateArrow);

	// a�ade valor a la propia carta si esta en centro - si el n�mero de cartas a izq/der/arr/abj son el mismo
	void addValueCenter(int boardSide, int add, Cell* cardCell);

	// a�ade valor a la propia carta si esta en esquina - si solo tiene dos casilla adyacentes en cualquier dir
	void addValueCorner();

	// bloquea el efecto de la carta en alguna direccion
	void blockCard(enum Direction);	

	// indica que esta carta no se puede bloquear
	bool unblockable();								
};

