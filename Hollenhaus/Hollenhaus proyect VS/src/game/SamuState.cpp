#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ColliderRender.h"
#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"

#include "CardFactory_v0.h"

#include "Factory.h"

#include "BoardFactory.h"

#include "MatchManager.h"

#include "BoardManager.h"
#include "TextComponent.h"
#include "MatchManager.h"

SamuState::SamuState() : GameState() {

	// Entidad match manager para preguntar por los turnos. La entidad es un Handler para tener acesso a ella facilmente
	auto matchManager = Instantiate();
	GameStateMachine::instance()->getMngr()->setHandler(ecs::hdlr::MATCH_MANAGER, matchManager);
	matchManager->addComponent<MatchManager>(4, MatchManager::TurnState::TurnJ2);

	cardFact = new CardFactory_v0();

	boardFact = new BoardFactory(4, 4);
	board = boardFact->createBoard();

	cardFact->createHand();

	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
	ent->getComponent<DragManager>()->setBoardManager(board->getComponent<BoardManager>());

	ecs::entity_t background = Instantiate();
	background->addComponent<Transform>();
	background->getComponent<Transform>()->getGlobalScale().set(0.42, 0.56);
	background->addComponent<SpriteRenderer>("board");
	background->setLayer(-1);

	ecs::entity_t pruebaTxt = Instantiate(Vector2D(400, 50));
	pruebaTxt->addComponent<TextComponent>("Buenas tardes a los que ya han comido", "8bit", SDL_Color({ 255, 255, 255, 255 }), TextComponent::Alignment::Center);
}

SamuState::~SamuState()
{
	delete boardFact;
	delete cardFact;
}
//cleon: si est� vac�o se llama directamente al padre
void SamuState::refresh()
{
	GameState::refresh();
}

void SamuState::update()
{
	system("CLS");

	GameState::update();

	board->getComponent<BoardManager>()->updateScore();

	std::cout << "Player 1 points: " << board->getComponent<BoardManager>()->getPlayer1Points() << std::endl;
	std::cout << "Player 2 points: " << board->getComponent<BoardManager>()->getPlayer2Points() << std::endl;

}

void SamuState::render() const
{
	GameState::render();
}
