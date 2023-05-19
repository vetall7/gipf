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
