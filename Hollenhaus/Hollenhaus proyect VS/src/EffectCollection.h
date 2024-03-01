#pragma once
#include "game/Card.h"
#include "Cell.h"
#include "game/Board.h"

namespace EffectType
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
public:
	EffectCollection();

	// ---- TIPOS DE EFECTOS ----
	// a�ade valor a algunas o todas sus adyacentes
	static void addAdj(Cell* cell, CellData::Direction direction, int add, bool ultimateArrow);
	static void addSimpleAdj(Cell* cell, CellData::Direction direction, int add);
	static void addSuperAdj(Cell* cell, CellData::Direction direction, int add);

	// a�ade valor a la propia carta si esta en centro - si el n�mero de cartas a izq/der/arr/abj son el mismo
	static void addCenter(Cell* cell, int add);

	// a�ade valor a la propia carta si esta en esquina - si solo tiene dos casilla adyacentes en cualquier dir
	static void addCorner(Cell* cell, int add);

	// bloquea el efecto de la carta en alguna direccion
	static void blockCard(Cell* cell, CellData::Direction direction);

	// indica que esta carta no se puede bloquear
	static void unblockable(Cell* cell, bool isUnblockable);


	/// En funcion del indice, devuelve el callback del efecto
	///	*** Esto es terrible, quiero que sirva para salir al paso
	///	y como concepto inicial ***
	static std::function<void()> getEffect(
		EffectType::Index index,
		Card* card,
		int value,
		CellData::Direction direction)
	{
		std::function<void()> effect;
		switch (index)
		{
		case EffectType::Esquina:
			effect = [card, value]
			{
				addCorner(card->getCell(), value);
			};
			break;
		case EffectType::Centro:
			effect = [card, value]
			{
				addCenter(card->getCell(), value);
			};
			break;
		case EffectType::Flecha:
			effect = [card, direction, value]
			{
				addSimpleAdj(card->getCell(), direction, value);
			};
			break;
		case EffectType::Superflecha:
			effect = [card, direction, value]
			{
				addSuperAdj(card->getCell(), direction, value);
			};
			break;
		case EffectType::Block:
			effect = [card, direction]
			{
				blockCard(card->getCell(), direction);
			};
			break;
		case EffectType::Unblockable:
			effect = [card]
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
