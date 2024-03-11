#pragma once
#include "checkML.h"
#include "GameState.h"
#include "NPC.h"
#include "Manager.h"
#include "MoveOnClick.h"

class MovementState : public GameState
{
public:
	MovementState();

	void update() override;
	void render() const override;
	void refresh() override;

	void onEnter() override;
	void onExit() override;

private:
	float scrollSpeed = 1.0f;
};

