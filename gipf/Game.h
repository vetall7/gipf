#pragma once
#include "Stone.h"
#include "Player.h"
#include <vector>
#include <string>
#include "CellState.h"
using namespace std;

class Point {
    int x, y;
public: 
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int GetX(){
        return x;
    }
    int GetY() {
        return y;
    }
};

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
    void Transfer(int x, int y, vector<Point>& line);
    bool IsLine(vector<Point>& line);
    void CheckLeftLine(vector<Point>& left_line, Point& i);
    void CheckRightLine(vector<Point>& right_line, Point& i);
    void CheckHorizontalLine(vector<Point>& horizontal_line, Point& i);
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