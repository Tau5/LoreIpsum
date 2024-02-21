#include "Board.h"
#include <iostream>
#include <stdLib.h>

Board::Board(int s) : size(s)
{
	initGrid();
}

Board::~Board()
{
	deleteGrid();
}

/// DEBUG ONLY: Pinta el tablero en consola
void Board::paintBoard()
{
	// para colorear poner 
	// system("Color E4");
	// siendo E el color de fondo y 4 el del texto
	// despues poner de vuelta el 
	// system("Color 07") para blanco y negro

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

	// recorre todas las casillas del grid y pinta las cartas
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// si la casilla no esta vacia
			if (grid[i][j]->getCard() != nullptr)
			{
				if (grid[i][j]->getPlayer() == PLAYER1) // gestiona el color
					SetConsoleTextAttribute(hConsole, 33);
				else if (grid[i][j]->getPlayer() == PLAYER2)
					SetConsoleTextAttribute(hConsole, 26);

				std::cout << getCellInfo(grid[i][j]); // pinta la carta

				SetConsoleTextAttribute(hConsole, 15);
				//system("Color 07");	// vuelve al negro
			}
			else // si la casilla esta vacia
			{
				std::cout << "[ -/-/---- ]";
			}
			std::cout << "  ";
		}
		std::cout << "\n";
	}
}

/// Devuelve si una carta dada por las coordenadas i, j es controlada por el jugador 'player'
bool Board::isPlayer(int i, int j, Owner player)
{
	return grid[j][i]->getPlayer() == player;
}

///  Juega una carta del jugador 'o' en la celda de posicion x, y del tablero
bool Board::setCard(int x, int y, Card* c, Owner o)
{
	Cell* cell = grid[y][x];
	if (cell->getCard() != nullptr)
		return false;
	cell->setCard(c, o);
	cell->addEffect(c->getEffect());
	cell->applyValue(c);
	return true;
}


/// DEBUG ONLY: Devuelve un string con los datos de la carta de la celda;
std::string Board::getCellInfo(Cell* cell) const
{
	std::string info = "["
		+ std::to_string(cell->getCard()->getCost()) + "/"
		+ std::to_string(cell->getCard()->getValue()) + "/"
		+ cell->getCard()->getSkill()
		+ "]";

	return info;
}

/// Devuelve los efectos aplicados en una celda dada
std::string Board::getEffects(Cell* cell) const
{
	return cell->getEffectHistory();
}


/// Metodo para generar un tablero ejemplo inicial
void Board::initGrid()
{
	resetGrid();
	std::string effect1 = "+2->";
	std::string effect2 = "-1<-";


	setCard(0, 2, new Card(0, 1, effect1), PLAYER1);
	setCard(2, 0, new Card(1, 2), PLAYER1);
	setCard(0, 3, new Card(2, 3, effect2), PLAYER2);
	setCard(1, 0, new Card(3, 4), PLAYER2);
}


/// Metodo que borra el tablero y lo reinicializa con casillas vacias
void Board::resetGrid()
{
	grid.clear();
	std::vector<Cell*> line;
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			line.push_back(new Cell());
		}
		grid.push_back(line);
		line.clear();
	}
}

/// Metodo para borrar todas las celdas del tablero
void Board::deleteGrid() const
{
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			delete grid[j][i];
}
