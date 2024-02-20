#include "ColliderRender.h"
#include "../sdlutils/SDLUtils.h"
#include "Manager.h"
#include "../Transform.h"
#include "../BoxCollider.h"



ColliderRender::ColliderRender()
{
}


ColliderRender::~ColliderRender()
{
}

void ColliderRender::initComponent()
{
	myTransform = mngr_->getComponent<Transform>(ent_);
	myBoxCollider = mngr_->getComponent<BoxCollider>(ent_);
}

void ColliderRender::render() const
{

	Vector2D pos = myTransform->getGlobalPos() + myBoxCollider->getPosOffset();
	//render debug
	SDL_Rect rect = build_sdlrect(pos,//pos
								myBoxCollider->getSize().getX(),//width
								myBoxCollider->getSize().getY());//heigth

	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(sdlutils().renderer(), &rect);
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 0, 0, 255);
}
