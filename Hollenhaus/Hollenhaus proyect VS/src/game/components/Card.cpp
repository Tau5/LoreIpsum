#include "pch.h"
#include "Card.h"
#include <string>

Card::Card() 
{

}

Card::Card(int cost, int value) : cost(cost), value(value)
{
}

Card::Card(int cost, int value, std::string& sprite, bool unblockable)
	: cost(cost), value(value), sprite(sprite), unblockable(unblockable)
{
	
}

// mete en la lisa de efectos el efecto indicado
void Card::addCardEffect(SDLEventCallback effectCallback)
{
	// el efecto a hacer push back deberia ser un metodo especifico de la coleccion
	effects.push_back(effectCallback);
}
