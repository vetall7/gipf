#include "Game.h"
#include <iostream>

Game::Game()
{

}

Game::Game(int size)
{
    board.resize(size);
}

void Game::SetCell(int x, int y, CellState cell)
{
    if (y >= board.size()) {
        board.resize(y + 1, vector<CellState>(0));
    }
    if (x >= board[y].size()) {
        board[y].resize(x + 1, CellState::Empty);
    }
    board[y][x] = cell;
}

void Game::DrawWorld()
{
    bool is;
    cout << board.size() << endl;
    cout << board[3].size() << endl;
    /*for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == CellState::Empty &&) {
                cout << "-";
            }
            else if (board[i][j] == CellState::White) {
                cout << "W";
            }
            else if (board[i][j] == CellState::Black) {
                cout << "B";
            }
        }
        cout << endl;
    }*/
}