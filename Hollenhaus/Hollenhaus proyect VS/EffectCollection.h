#pragma once
#include <functional>

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void(void)>;

class EffectCollection
{
private:
	std::list<SDLEventCallback> effectCallbacks;

public:
	// 
	void subscribeToCallback(SDLEventCallback effectCallback);

	// ---- TIPOS DE EFECTOS ----
	void addValueAdj(enum Direction, int add);		// a�ade valor a algunas o todas sus adyacentes
	void addValueCenter();							// a�ade valor a la propia carta si esta en centro - si el n�mero de cartas a izq/der/arr/abj son el mismo
	void addValueCorner();							// a�ade valor a la propia carta si esta en esquina - si solo tiene dos casilla adyacentes en cualquier dir
	void blockCard(enum Direction);					// bloquea el efecto de la carta en agluna direccion
	bool unblockable();								// indica que esta carta no se puede bloquear
};

