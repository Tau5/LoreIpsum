#include "pch.h"
#include "DragManager.h"
#include "../../../sdlutils/InputHandler.h"
#include "../basics/Transform.h"
#include "Manager.h"
#include "../../GameStateMachine.h"
#include "../basics/BoxCollider.h"
#include "../DropDetector.h"
#include "CardStateManager.h"

#include "../Cell.h"
#include "../Card.h"
#include "BoardManager.h"
#include "../HandComponent.h"
#include "MatchManager.h"

DragManager::DragManager()
{
}

DragManager::~DragManager()
{
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void DragManager::initComponent()
{
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });

	dragTransform = nullptr;
}

void DragManager::update()
{
	//si tenemos carta drageada...

	if (dragTransform != nullptr) {
		//actualizamos su posicion teniendo en cuenta la posicion del raton

		Vector2D mousePos (ih().getMousePos().first, ih().getMousePos().second);
		Vector2D posAct = (mousePos - initialMousePos) + initialTransformPos;

		dragTransform->setGlobalPos(posAct);
	}

}

void DragManager::OnLeftClickDown()
{
	//buscar una colision con una entidad del grupo carta

	auto card = mouseRaycast(ecs::grp::CARDS);

	const auto matchManager = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>();

	const Players::Owner turnOwner = matchManager->getActualState() == MatchManager::TurnJ1
		? Players::PLAYER1 : Players::PLAYER2;

	Players::Owner cardOwner = Players::NULO;

	//setear la carta en funcion de donde hemos clickado
	if (card != nullptr
		&& card->getComponent<Transform>() != nullptr
		&& card->getComponent<Transform>()->getParent() != nullptr) {

		cardOwner = card->getComponent<Transform>()->getParent()->getEntity()->getComponent<HandComponent>()->getOwner();
	}


	if (card != nullptr && //si hay carta y esta en la mano
		card->getComponent<CardStateManager>()->getState() == CardStateManager::ON_HAND && 
		cardOwner == turnOwner)  // si es carta del propietario del turno actual
	{

		//se guarda la posicion/ transform de como estaba la carta
		dragTransform = card->getComponent<Transform>();

		initialTransformPos.set(dragTransform->getGlobalPos());
		initialMousePos.set(Vector2D(ih().getMousePos().first, ih().getMousePos().second));

		//dragTransform->getGlobalPos().set(ih().getMousePos().first, ih().getMousePos().second);
	}


}

void DragManager::OnLeftClickUp()
{
	//si no tenemos carta drageada, no hacemos nada

	//si, s� la tenemos, verifcamos colisiones con el grupo DropDetector
	if (dragTransform != nullptr) {

		auto drop = mouseRaycast(ecs::grp::DROPS);

		auto dropDetector = drop != nullptr ? drop->getComponent<DropDetector>() : nullptr;

		//si tenemos una colision con el drop detector, cambiamos la posicion de la carta por la que guarde el drop
		//también confirmamos que tenemos suficientes puntos de acción para lanzar la carta
		if (drop != nullptr && 
			!dropDetector->isOcuped() && 
			dragTransform->getEntity()->getComponent<Card>()->getCost() <= mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getActualPlayerActualActionPoints()			)
		{
			dragTransform->setGlobalPos(dropDetector->getCardPos());
			
			dragTransform->getEntity()->getComponent<CardStateManager>()->setState(CardStateManager::ON_CELL);
			dragTransform->getEntity()->getComponent<CardStateManager>()->putOnBoard();

			dropDetector->setOcuped(true);

			//x,y dependen del dropDectector(Cell)
			//card viene del dragTransform
			//owner depende del match manager,
			
			int x = dropDetector->getBoardPos().getX();
			int y = dropDetector->getBoardPos().getY();
			Card* card = dragTransform->getEntity()->getComponent<Card>();
			
			Players::Owner playerTurn = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getPlayerTurn();
			boardManager->setCard(x, y, card, playerTurn);
		}
		else {//sino, devolvemos la carta a su posicion inicial
			dragTransform->setGlobalPos(initialTransformPos);
		}

		//en cualquier caso, ya no tenemos carta drageada

		dragTransform = nullptr;
	}

}
