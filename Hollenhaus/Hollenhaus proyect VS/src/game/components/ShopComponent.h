#pragma once

#include <list>


const int CARDS_IN_SHOP = 4; // Cantidad de cartas de la tienda.
const int COST_PER_COST = 100; // Precio que suma el coste de la carta al precio total.
const int COST_PER_EFFECTS = 100; // Precio que suma cada efecto al precio total. Se multiplica este numero por numero de efectos.

class Card;
class Button;

class ShopComponent : public ComponentUpdate
{
public:

	//------Constructora.
	ShopComponent();
	//------Destructora.
	~ShopComponent();

	//------Inicializacion del componente.
	void initComponent() override;


	void update() override;

	//------Genera las CARDS_IN_SHOP cartas que puede comprar el jugador.
	void generateCards();
	//------Comprueba si una carta ha sido comprada por el jugador, es decir, esta en el drawer (cajon).
	bool cardIsBought(int id);
	//------Muestra las cartas disponibles para comprar.
	void showCards();
	//------Muestra los precios de las cartas.
	void showPrizes();
	//------Logica de la compra.
	void buyCard();
	//------Para abrir el di�logo de confirmacion de compra.
	bool confirmPurchase();
	//------Dada una carta calcula su precio seg�n su coste y modificadores.
	int calculatePrize(ecs::entity_t card);
	//------Dado un id de una carta, devuelve su poscion en shopCards, shopCardsPrize y shopCardsPositions porque comparten indexacion.
	int searchIndexById(int id);
	//------Settea los textos de dinero y precio de las cartas.
	void setTexts();
	//------Actualiza los textos de dinero y precio de las cartas.
	void updateTexts();
private:
	//----Guarda las CARDS_IN_SHOP cartas de la tienda.
	int* shopCards;
	//----Precio de las cartas.
	int* shopCardsPrize;
	//----Guarda las posiciones de las cartas.
	Vector2D* shopCardsPositions;
	//----Guarda las cartas creadas para luego interactuar con ellas.
	std::list<Card*> buyableCards;
	//----Guarda los botones para luego poder acceder a la entidad del boton clickado.
	std::list<Button*> buttons;
	//----Dinero del jugador:
	int money;
	//------------------------------lo del precio de las cartas deberia de estar en el json. Todas en el mismo json.
	//----Texto que muestra el dinero.
	ecs::entity_t moneyText;
	//----Texto que muestra el precio de la carta 0.
	ecs::entity_t cardPrizeText0;
	//----Texto que muestra el precio de la carta 1.
	ecs::entity_t cardPrizeText1;
	//----Texto que muestra el precio de la carta 2.
	ecs::entity_t cardPrizeText2;
	//----Texto que muestra el precio de la carta 3.
	ecs::entity_t cardPrizeText3;
};

