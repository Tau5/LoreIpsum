#pragma once
#include <string>
#include "Entity.h"
#include <functional>

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void()>;



#include "ComponentUpdate.h"

class Card : public ComponentUpdate
{
	// lo de adelante es placeholder! para comprobar que funca bien el parseado de jsons que todavia no hay entities ni componentes
	int cost, value;
	std::string sprite, skills;

	std::list<SDLEventCallback> cardEffectCallbacks; // lista de los efectos que tiene una carta concreta
	std::list<SDLEventCallback>::iterator cardEffectIT;

	//SDLEventCallback effectCallback;

public:
	Card();
	Card(int, int);
	Card(int, int, std::string&);
	Card(int, int, std::string&, std::string&);
	Card(int, int, std::string);

	// adds a skill to the skills of the card
	void addSkill(std::string& s) { skills += " " + s; }

	void addCardEffect(SDLEventCallback buttonCallback);

	// getters
	int getCost() const { return cost; }
	int getValue() const { return value; }
	std::string getSkill() { return skills; }
	SDLEventCallback getEffect(int i) {

		cardEffectIT = cardEffectCallbacks.begin();
		std::next(cardEffectIT, i);	// avanza x posiciones

		return *(cardEffectIT);
	}

	// setters
	void setCost(int v) { cost = v; }
	void setValue(int v) { value = v; }
	void setSprite(const std::string& v) { sprite = v; }
	void setSkills(const std::string& v) { skills = v; }
};
