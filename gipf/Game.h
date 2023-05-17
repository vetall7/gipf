#pragma once
#include "Stone.h"
#include <vector>
#include "CellState.h"
using namespace std;

class Game {
private:
    vector<vector<CellState>> board;
public:
    Game();
    Game(int size);
    void SetCell(int x, int y, CellState cell);
    void DrawWorld();
};