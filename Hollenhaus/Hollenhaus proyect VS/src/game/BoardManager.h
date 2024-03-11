#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include <list>
#include <iostream>
#include <functional>
#include "../Cell.h"

class Card;
using SDLEventCallback = std::function<void()>;

class BoardManager : public ComponentUpdate
{
public:
    BoardManager();
    BoardManager(int);
    ~BoardManager() override;

    void initComponent() override;
    void update() override;

    bool isFull() const;
    void updateScore();

    /// Setters
    bool setCard(int x, int y, Card* c, CellData::Owner o); // true si pudo poner carta (no habia otra ya antes)

    /// Getters
    int getPlayer1Points() const { return pPlayer1; }
    int getPlayer2Points() const { return pPlayer2; }
    Cell* getCell(int x, int y) const;
    std::list<SDLEventCallback> getEffects(Cell* cell) const;

    void setBoard(std::vector<std::vector<ecs::entity_t>>& board) { 
        _board = board;
        initBoard(); 
    }

private:
    void initBoard();
    //cleon: si en la entrega es una constante, os matar�. bueno, yo os matar�
    int size; 

    // Un vector de vectores de entidades "Cell".
    std::vector<std::vector<ecs::entity_t>> _board;

    int cardsOnBoard = 0;

    /// match manager
    void applyAllEffects() const;
    int pPlayer1 = 0;
    int pPlayer2 = 0;
    ecs::entity_t p1Text;
    ecs::entity_t p2Text;
};

