#pragma once
#include <list>

class ShopComponent : public ComponentUpdate
{public:

	ShopComponent();
	~ShopComponent();

	//------Inicializacion del componente.
	void initComponent() override;

	//------Genera las 4 cartas que puede comprar el jugador.
	void generateCards();
	//------Comprueba si una carta ha sido comprada por el jugador, es decir, esta en el drawer (cajon).
	bool checkCardIsBought(int id);
	//------Muestra las cartas disponibles para comprar.
	void showCards();
	//------Muestra los precios de las cartas.
	void showPrizes();

private:
	//----Guarda las 4 cartas de la tienda.
	int* shopCards; 

	//------------------------------lo del precio de las cartas deberia de estar en el json. Todas en el mismo json.
	//------------------------------array de vector2d de posiciones fijas para las cartas.
	//------------------------------array de precios de las cartas. Sus posiciones son las de las cartas pero bajando la y.
	
};
