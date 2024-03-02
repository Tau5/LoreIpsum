#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "SamuState.h"
#include "JimboState.h"
#include "AndresState.h"
#include "LuisState.h"
#include "Manager.h"
#include "Mouse.h";
#include "BoardState.h"


void GameStateMachine::init()
{
	mngr_ = new ecs::Manager();
	mouse_ = new Mouse("mouse", 2);
	//pushState(new LuisState());
	//pushState(new JimboState());
	//pushState(new AndresState());
	
	//pushState(new BoardState());
	pushState(new SamuState());
	//pushState(new LuisState());
}

//constructor
GameStateMachine::GameStateMachine()
{
	//init();
	//inicializamos la pila con el estado del menu inicial
}

//destructor
GameStateMachine::~GameStateMachine() {

	//destruye uno a uno todos los estados apilados que queden
	while (!gameStack.empty()) {
		delete gameStack.top();
		gameStack.pop();
	}
	delete mouse_;
	delete mngr_;
}


void GameStateMachine::Render() const{
	if (Empty()) return;
	gameStack.top()->render();
	mouse_->render();
}

void GameStateMachine::Update() {
	if (Empty()) return;
	gameStack.top()->update();
	mouse_->update();
	//para el manager
	Refresh();
}

void GameStateMachine::Refresh()
{
	gameStack.top()->refresh();
}

void GameStateMachine::pushState(GameState* state) {
	gameStack.push(state);
}

void GameStateMachine::replaceState(GameState* state) {
	popState();
	pushState(state);
}

void GameStateMachine::popState() {
	toBeDeleted.push_back(gameStack.top());
	gameStack.pop();
}