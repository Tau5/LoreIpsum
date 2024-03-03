#include "CityState.h"
CityState::CityState()
{
	std::cout << "\nLoading City";
}
void CityState::update()
{
	GameState::update();
}
void CityState::render() const
{
	GameState::render();
}
void CityState::refresh()
{
	GameState::refresh();
}

void CityState::onEnter()
{
	std::cout << "\nentering CityState\n";
	
	//-----Ciudad de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("ciudadcompleta");
	fondo->getComponent<Transform>()->getGlobalScale().set(0.495f, 0.495f);
	fondo->setLayer(0);

	//------NPCs que demomento son Caitlyns:
	ecs::entity_t npc2 = Instantiate();
	npc2->addComponent<Transform>();
	npc2->addComponent<SpriteRenderer>("npc");
	npc2->addComponent<BoxCollider>();
	npc2->getComponent<Transform>()->getGlobalScale().set(0.25f, 0.25f);
	Vector2D np2Pos(200, 425);
	npc2->getComponent<Transform>()->setGlobalPos(np2Pos);
	npc2->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc2->addComponent<NPC>(2); // Lleva a la oficina (2).
	npc2->setLayer(2);

	ecs::entity_t npc1 = Instantiate();
	npc1->addComponent<Transform>();
	npc1->addComponent<SpriteRenderer>("npc");
	npc1->addComponent<BoxCollider>();
	npc1->getComponent<Transform>()->getGlobalScale().set(0.25f, 0.25f);
	Vector2D np1Pos(600, 425);
	npc1->getComponent<Transform>()->setGlobalPos(np1Pos);
	npc1->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc1->addComponent<NPC>(3); // Lleva a la tienda (3).
	npc1->setLayer(2);

	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	exit->addComponent<NPC>(0); // Lleva al menu (0).
	exit->setLayer(2);
}

void CityState::onExit()
{
	std::cout << "\nexit CityState\n";
	GameStateMachine::instance()->getMngr()->Free();
}
