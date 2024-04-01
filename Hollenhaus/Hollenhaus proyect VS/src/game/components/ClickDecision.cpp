#include "pch.h"
#include "ClickDecision.h"

#include "../components/NextText.h"
#include "../components/DialogueDestroyer.h"

ClickDecision::ClickDecision(int decision, ecs::entity_t parent)
{
	decision_ = decision;
	parent_ = parent;
	click_ = false;

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

void ClickDecision::initComponent()
{
}

void ClickDecision::update()
{
}

void ClickDecision::OnLeftClickDown()
{
	if (mouseRaycast() == ent_)
	{
		click_ = true;
		TakeDecision();
	}
}

void ClickDecision::OnLeftClickUp()
{
	click_ = false;
}

void ClickDecision::TakeDecision()
{
	switch (decision_) 
	{
	case 0:
		TuVieja("SI");
		//llamar al callEvent
		break;

	case 1:
		TuVieja("BYEBYE");
		parent_->getComponent<NextText>()->setDead(true);
		parent_->getComponent<DialogueDestroyer>()->destroyDialogue();
		break;

	default:
		TuVieja("Esta decision no existe. A�adir en ClickDecision.cpp");
		break;
	}
}


