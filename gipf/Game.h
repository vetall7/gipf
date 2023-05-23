#pragma once
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
    int GetX() const{
        return x;
    }
    int GetY() const{
        return y;
    }
    bool operator==(const Point& rhs) const {
        return this->GetX() == rhs.GetX() && this->GetY() == rhs.GetY();
    }
    bool operator<(const Point& rhs) const {
        if (x < rhs.x) {
            return true;
        }
        else if (x == rhs.x) {
            return y < rhs.y;
        }
        return false;
    }
    bool operator>(const Point& rhs) const {
        if (x > rhs.x) {
            return true;
        }
        else if (x == rhs.x) {
            return y > rhs.y;
        }
        return false;
    }
    Point& operator=(const Point& rhs) {
        if (this == &rhs) {
            return *this;
        }
        x = rhs.x;
        y = rhs.y;
        return *this;
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
    string game_state;
    bool is_white_turn;
    int size;
    int stones_in_line;
    void ConvertCoordinate(string coo, int& x, int& y);
    void GenerateMoves(vector<string>& coordinates, string& from);
    void Move(int x, int y, vector<vector<Point>>& to_delete);
    void DirectionDetect(string from, string to);
    void Transfer(int x, int y, vector<Point>& line);
    bool IsLine(vector<Point>& line);
    void CheckLeftLine(vector<Point>& left_line, Point& i);
    void CheckRightLine(vector<Point>& right_line, Point& i);
    void CheckHorizontalLine(vector<Point>& horizontal_line, Point& i);
    bool BoardCheck();
    Direction direction;
public:
    Game();
    Game(int size, Player& first, Player& second);
    void SetCell(int x, int y, CellState cell);
    void DrawWorld();
    void ReadBoard(int size);
    void SetPlayers(Player& first, Player& second);
    void SetSize(int size);
    void SetStoneLine(int stones);
    int GetSize();
    void DoMove(string from, string to, vector<string>& delete_points);
    void SetTurn(bool turn);
    void PrintState();
};