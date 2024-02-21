#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "../SpriteRenderer.h"
#include "../Transform.h"
#include "../BoxCollider.h"
#include "ColliderRender.h"
#include "Drag.h"

SamuState::SamuState() : GameState() {

	auto mngr = GameStateMachine::instance()->getMngr();

	card = mngr->addEntity();
	
	mngr->addComponent<Transform>(card);
	mngr->addComponent<SpriteRenderer>(card, "card");
	mngr->addComponent<BoxCollider>(card);
	mngr->addComponent<Drag>(card);

	auto cardTransform = mngr->getComponent<Transform>(card);

	cardTransform->getGlobalScale().set(0.4, 0.4);
	cardTransform->getGlobalPos().set(100, 100);	


}

SamuState::~SamuState()
{

}

void SamuState::refresh()
{
	GameState::refresh();
}

void SamuState::update()
{
	GameState::update();

	
}

void SamuState::render() const
{
	GameState::render();
}
