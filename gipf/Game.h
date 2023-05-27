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
    int GetX() const {
        return x;
    }
    int GetY() const {
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
    CellState WhoTakes;
    string game_state;
    bool is_white_turn, is_turn_committed, is_good_index, is_good_color;
    int size;
    int stones_in_line;
    void ConvertCoordinate(string coo, int& x, int& y);
    void GenerateMoves(vector<string>& coordinates, string& from);
    void Move(int x, int y, vector<vector<Point>>& to_delete, bool is_test_move);
    void DirectionDetect(string from, string to);
    void Transfer(int x, int y, vector<Point>& line, bool is_just_checking);
    bool IsLine(vector<Point>& line);
    void CheckLeftLine(vector<Point>& left_line, Point& i);
    void CheckRightLine(vector<Point>& right_line, Point& i);
    void CheckHorizontalLine(vector<Point>& horizontal_line, Point& i);
    bool BoardCheck();
    void DeleteStones(vector<vector<Point>>& to_delete, vector<vector<Point>>& lines_to_delete);
    bool IsGoodCoordinate(string coo, bool is_start);
    bool IsGoodField(string coo, bool is_start);
    int isNoDeletedLines();
    Direction direction;
public:
    bool AllMoves();
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
    void SetWhoTakes(CellState player);
};