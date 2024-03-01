#pragma once
#include "game/Card.h"
#include "Cell.h"
#include "game/Board.h"

namespace Effects
{
	enum Index
	{
		Esquina,
		Centro,
		Flecha,
		Superflecha,
		Block,
		Unblockable,

		_NO_DISCARD_
	};
}

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
	static void addAdj(Cell* thisCardCell, CellData::Direction direction, int add, bool ultimateArrow);
	static void addSimpleAdj(Cell* thisCardCell, CellData::Direction direction, int add);
	static void addSuperAdj(Cell* thisCardCell, CellData::Direction direction, int add);

	// a�ade valor a la propia carta si esta en centro - si el n�mero de cartas a izq/der/arr/abj son el mismo
	static void addCenter(Cell* thisCardCell, int add);

	// a�ade valor a la propia carta si esta en esquina - si solo tiene dos casilla adyacentes en cualquier dir
	static void addCorner(Cell* thisCardCell, int add);

	// bloquea el efecto de la carta en alguna direccion
	static void blockCard(Cell* thisCardCell, CellData::Direction direction);

	// indica que esta carta no se puede bloquear
	static void unblockable(Cell* thisCardCell, bool isUnblockable);


	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto general, pero no me juzgues mucho ***
	template <typename T>
	static std::function<void()> getEffect(
		T ref,
		Effects::Index index,
		Card* card,
		int value,
		CellData::Direction direction)
	{
		std::function<void()> effect;
		switch (index)
		{
		// std::forward<Ts>(args)...
		case Effects::Esquina:
			effect = [ref, card, value]
			{
				addCorner(card->getCell(), value);
			};
			break;
		case Effects::Centro:
			effect = [ref, card, value]
			{
				addCenter(card->getCell(), value);
			};
			break;
		case Effects::Flecha:
			effect = [ref, card, direction, value]
			{
				addSimpleAdj(card->getCell(), direction, value);
			};
			break;
		case Effects::Superflecha:
			effect = [ref, card, direction, value]
			{
				addSuperAdj(card->getCell(), direction, value);
			};
			break;
		case Effects::Block:
			effect = [ref, card, direction]
			{
				blockCard(card->getCell(), direction);
			};
			break;
		case Effects::Unblockable:
			effect = [ref, card]
			{
				unblockable(card->getCell(), card->getIsUnblockable());
			};
			break;
		default:
			break;
		}

		return effect;
	}
};
