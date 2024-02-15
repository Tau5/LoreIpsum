#include "SpriteRenderer.h"
#include "Transform.h"

SpriteRenderer::SpriteRenderer(const std::string & _textPath): texturePath(_textPath)
{
	initCompomnent();
};

// Para inicializar el componenete si es necesario.
void SpriteRenderer::initCompomnent() {
	texture = new Texture(sdl.renderer(), texturePath);
};

// Para renderizar el estado
void SpriteRenderer::render() const {
	
	texture->render(transform->getGlobalPos().getX(),
		transform->getGlobalPos().getY(),
		transform->getGlobalScale().getX(),
		transform->getGlobalScale().getY(),
		transform->getGlobalAngle());
	
};