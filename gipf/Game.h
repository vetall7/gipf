#pragma once
#include "Stone.h"
#include "Player.h"
#include <vector>
#include <string>
#include "CellState.h"
using namespace std;

enum Direction {
    Right,
    Left,
    RightDown,
    LeftDown,
    RightUp,
    LeftUp
};


class Game {
private:
    vector<vector<CellState>> board;
    Player WhitePlayer;
    Player BlackPlayer;
    bool is_white_turn;
    int size;
    void ConvertCoordinate(string coo, int& x, int& y);
    void GenerateMoves(vector<string>& coordinates, string& from);
    void Move(int x, int y);
    void DirectionDetect(string from, string to);
    void Transfer(int x, int y);
    Direction direction;
public:
    Game();
    Game(int size, Player& first, Player& second);
    void SetCell(int x, int y, CellState cell);
    void DrawWorld();
    void ReadBoard(int size);
    void SetPlayers(Player& first, Player& second);
    void SetSize(int size);
    int GetSize();
    void DoMove(string from, string to, vector<string>& delete_points);
    void SetTurn(bool turn);
};