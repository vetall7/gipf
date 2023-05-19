#pragma once
#include "Stone.h"
#include "Player.h"
#include <vector>
#include "CellState.h"
using namespace std;

class Game {
private:
    vector<vector<CellState>> board;
    Player WhitePlayer;
    Player BlackPlayer;
    int size;
public:
    Game();
    Game(int size, Player& first, Player& second);
    void SetCell(int x, int y, CellState cell);
    void DrawWorld();
    void ReadBoard(int size);
    void SetPlayers(Player& first, Player& second);
    void SetSize(int size);
    int GetSize();
};