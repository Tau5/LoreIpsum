#pragma once
#include "game/Card.h"
#include "Cell.h"
#include "game/Board.h"

class EffectCollection
{
private:
	Card* card;
	Board* board;
	Cell* cell;


public:

	EffectCollection();

	// ---- TIPOS DE EFECTOS ----
	// a�ade valor a algunas o todas sus adyacentes
	static void addValueAdj(Cell* thisCardCell, CellData::Direction direction, int add, bool ultimateArrow);

	// a�ade valor a la propia carta si esta en centro - si el n�mero de cartas a izq/der/arr/abj son el mismo
	static void addValueCenter(Cell* thisCardCell, int add);

	// a�ade valor a la propia carta si esta en esquina - si solo tiene dos casilla adyacentes en cualquier dir
	static void addValueCorner(Cell* thisCardCell, int add);

	// bloquea el efecto de la carta en alguna direccion
	static void blockCard(Cell* thisCardCell, CellData::Direction direction);

	// indica que esta carta no se puede bloquear
	static void unblockable(Cell* thisCardCell, bool isUnblockable);
};

