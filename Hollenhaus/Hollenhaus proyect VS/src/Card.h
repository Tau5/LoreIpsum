#pragma once
#include <string>
// #include "Entity.h"

class Card // : Entity
{
	// lo de adelante es placeholder! para comprobar que funca bien el parseado de jsons que todavia no hay entities ni componentes
	int cost, value;
	std::string sprite, skills;
	bool player; // Ines: lo a�ado porque me hace falta pero no se si lo quereis asi
public:
	Card() = default;
	Card(int, int, std::string&, std::string&);

	int getCost() {
		return cost;
	}

	int getValue() {
		return value;
	}

	std::string getSkill() {
		return skills;
	}

	bool getPlayer() {
		return player;
	}
};
