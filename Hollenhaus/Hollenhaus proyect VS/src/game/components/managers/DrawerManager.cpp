#include "pch.h"
#include "DrawerManager.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"

DrawerManager::DrawerManager() : cajonesAbiertos(0)
{
}

DrawerManager::~DrawerManager()
{
}

void DrawerManager::update()
{
}

void DrawerManager::initComponent()
{
	drawer = GameStateMachine::instance()->getCurrentState()->getDrawer();
}

void DrawerManager::addCard(int id)
{
	std::cout << drawer[id] << std::endl;
}

void DrawerManager::removeCard(int id)
{

}

void DrawerManager::drawerPalante()
{
	TuVieja("drawerPalante");
}

void DrawerManager::drawerPatras()
{
	TuVieja("drawerPatras");
}
