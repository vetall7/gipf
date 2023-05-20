#include "Game.h"
#include <iostream>

Game::Game()
{
}

Game::Game(int size, Player& first, Player& second) : WhitePlayer (first), BlackPlayer(second)
{
    board.resize(size);
}

void Game::SetCell(int x, int y, CellState cell)
{
    if (y >= board.size()) {
        board.resize(y + 1, vector<CellState>(0));
    }
    if (x >= board[y].size()) {
        board[y].resize(x + 1, CellState::None);
    }
    board[y][x] = cell;
}

void Game::DrawWorld()
{
    if (board.size() == 0) {
        cout << "THE BOARD IS EMPTY" << endl;
        return;
    }
    cout << endl;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == CellState::Empty) {
                cout << "_";
            }
            else if (board[i][j] == CellState::White) {
                cout << "W";
            }
            else if (board[i][j] == CellState::Black) {
                cout << "B";
            }
            else if (board[i][j] == CellState::Space) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void Game::ReadBoard(int size)
{
    char zn;
    int i = 0, j = 0;
    zn = getchar();
    int black_counter = 0, white_counter = 0;
    while (i != size * 2 - 1) {
        zn = getchar();
        if (zn == '\n') {
            i++;
            j = 0;
            continue;
        }
        if (zn == ' ') {
            SetCell(j, i, CellState::Space);
        }
        else if (zn == '_') {
            SetCell(j, i, CellState::Empty);
        }
        else if (zn == 'W') {
            SetCell(j, i, CellState::White);
            white_counter++;
        }
        else if (zn == 'B') {
            SetCell(j, i, CellState::Black);
            black_counter++;
        }
        j++;
    }
    if (white_counter + WhitePlayer.GetReserveStones() != WhitePlayer.GetStones()
        || black_counter + BlackPlayer.GetReserveStones() != BlackPlayer.GetStones()) {
        cout << "the number of stones does not match!!!!!" << endl;
        for (auto& innerVector : board) {
            innerVector.clear();
        }
        board.clear();
        board.resize(0);
    }
}

void Game::SetPlayers(Player& first, Player& second)
{
    WhitePlayer = first;
    BlackPlayer = second;
}

void Game::SetSize(int size)
{
    this->size = size;
}

int Game::GetSize()
{
    return size;
}


void Game::Transfer(int x, int y)
{
    int rangeX = 0, rangeY = 0;
    if (direction == Right) {
        rangeX = 2;
    }
    else if (direction == Left) {
        rangeX = -2;
    }
    else if (direction == RightDown){
        rangeX = 1, rangeY = 1;
    }
    else if (direction == LeftDown) {
        rangeX = -1;
        rangeY = 1;
    }
    else if (direction == RightUp) {
        rangeX = 1, rangeY = -1;
    }
    else if (direction == LeftUp) {
        rangeX = -1;
        rangeY = -1;
    }
    int x_temp = x + rangeX;
    int y_temp = y + rangeY;
    while (board[y_temp][x_temp] != CellState::Empty) {
        x_temp += rangeX;
        y_temp += rangeY;
        if ( y_temp < 0 || y_temp >= board.size() || x_temp < 0 || x_temp >= board[y_temp].size() || board[y_temp][x_temp] == CellState::Space) {
            cout << "YOU CANT" << endl;
            return;
        }
    }
    while (x_temp != x) {
        board[y_temp][x_temp] = board[y_temp - rangeY][x_temp - rangeX];
        x_temp -= rangeX;
        y_temp -= rangeY;
    }
}

void Game::Move(int x, int y)
{
    if (board[y][x] != CellState::Empty) {
        Transfer(x, y);
    }
    if (is_white_turn) {
        board[y][x] = CellState::White;
        is_white_turn = false;
    }
    else {
        board[y][x] = CellState::Black;
        is_white_turn = true;
    }
}


void Game::DirectionDetect(string from, string to)
{
    int index_x_from = from[0] - 'a';
    int index_y_from = from[1] - '0';
    int index_x_to = to[0] - 'a';
    int index_y_to = to[1] - '0';
    if (index_x_from + 1 == index_x_to && index_y_from + 1 == index_y_to) {
        direction = Right;
    }
    else if (index_x_from - 1 == index_x_to && index_y_from == index_y_to) {
        direction = Left;
    }
    else if (index_x_from + 1 == index_x_to && index_y_from == index_y_to) {
        direction = RightDown;
    }
    else if (index_x_from == index_x_to && index_y_from - 1 == index_y_to) {
        direction = LeftDown;
    }
    else if (index_x_from == index_x_to && index_y_from + 1 == index_y_to) {
        direction = RightUp;
    }
    else if (index_x_from - 1 == index_x_to && index_y_from + 1 == index_y_to) {
        direction = LeftUp;
    }
}

void Game::DoMove(string from, string to)
{
    vector<string>  coordinates;
    bool is_move = false;
    GenerateMoves(coordinates, from);
    for (string i : coordinates) {
        if (i == to) {
            is_move = true;
        }
    }
    if (is_move) {
        int x_to, y_to;
        ConvertCoordinate(to, x_to, y_to);
        DirectionDetect(from, to);
        cout << direction << endl;
        Move(x_to, y_to);
    }
    else {
        cout << "YOU CANT DO THIS MOVE" << endl;
    }
}

void Game::SetTurn(bool turn)
{
    is_white_turn = turn;
}

void Game::ConvertCoordinate(string coo, int &x, int &y)
{
    int index_x = coo[0] - 'b';
    int index_y = coo[1] - '0';
    int array_index_x = size - 1 + index_x*2;
    int i = size + 1 + index_x;
    int diff = i - index_y;
    i -= 2 * diff;
    index_y -= i;
    if (index_x >= size) {
        index_y -= index_x - size + 1;
    }
    array_index_x -= index_y;

    x = array_index_x;
    y = index_y;
}

void Game::GenerateMoves(vector<string>& coordinates, string& from)
{
    int index_x = from[0] - 'a';
    int index_y = from[1] - '0';
    int max = (size * 2 + 1) - (index_x - size); // макситмальное число которое может иметь буква
    if (index_y == 1 && index_x >= size) {
        if (index_x == size) {
            coordinates.push_back(string(1, from[0]) + "2");
        }
        else if (index_x == size*2) {
            coordinates.push_back(string(1, from[0] - 1) + "2");
        }
        else {
            coordinates.push_back(string(1, from[0]) + "2");
            coordinates.push_back(string(1, from[0] - 1) + "2");
        }
    }
    else if (index_y == 1) {
        if (index_x == 0){
            coordinates.push_back(string(1, from[0] + 1) + "2");
        }
        else {
            coordinates.push_back(string(1, from[0]) + "2");
            coordinates.push_back(string(1, from[0] + 1) + "2");
        }
    }
    else if (from[0] == 'a') {
        if (index_y == size+1) {
            coordinates.push_back(string(1, from[0] + 1) + to_string(index_y));
        }
        else {
            coordinates.push_back(string(1, from[0] + 1) + to_string(index_y));
            coordinates.push_back(string(1, from[0] + 1) + to_string(index_y + 1));
        }
    }
    else if (index_x == size * 2) {
        if (index_y == max) {
            coordinates.push_back(string(1, from[0] - 1) + to_string(index_y));
        }
        else {
            coordinates.push_back(string(1, from[0] - 1) + to_string(index_y));
            coordinates.push_back(string(1, from[0] - 1) + to_string(index_y + 1));
        }
    }
    else if (from[0] == 'a' + index_y - size - 1) {
        if (index_x == size) {
            coordinates.push_back(string(1, from[0]) + to_string(index_y - 1));
        }
        else {
            coordinates.push_back(string(1, from[0]) + to_string(index_y - 1));
            coordinates.push_back(string(1, from[0] + 1) + to_string(index_y));
        }
    }
    else if (index_y == max && index_x > size) {
        coordinates.push_back(string(1, from[0]-1) + to_string(index_y));
        coordinates.push_back(string(1, from[0]) + to_string(index_y-1));
    }
}
