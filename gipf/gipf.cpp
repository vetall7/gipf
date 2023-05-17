#include <iostream>
#include <vector>
#include "Game.h"
using namespace std;

int main()
{
    int size, length, white_stones, black_stones;
    cin >> size >> length >> white_stones >> black_stones;
    int white_reserves, black_reserves;
    cin >> white_reserves >> black_reserves;
    char first_player;
    cin >> first_player;
    //std::vector<std::vector<char>> array (size*2);
    cout << endl;
    Game game (size*2);
    char zn;
    cin >> zn;
    int i = 0, j = 0, przesun = size - 1;
    while (i != size*2 - 1) {
        zn = getchar();
        if (zn == '\n') {
            i++;
            j = 0;
            continue;
        }
        else if (zn == ' ' && j < przesun) {
            game.SetCell(j, i, CellState::Empty);
        }
        else if (zn == '-') {
            game.SetCell(j, i, CellState::Empty);
        }
        else if (zn == 'W') {
            game.SetCell(j, i, CellState::White);
        }
        else if (zn == 'B') {
            game.SetCell(j, i, CellState::Black);
        }
        j++;
        if (i <= size) {
            przesun--;
        }
        else if (i > size) {
            przesun++;
        }
    }

    game.DrawWorld();

    /*for (int i = 0; i < size*2; i++) {
        zn = getchar();
        while (zn != '\n') {
            array[i].push_back(zn);
            zn = getchar();
        }
    }
    for (int i = 0; i < size * 2; i++) {
        for (char j : array[i]) {
            cout << j;
        }
        cout << endl;
    }*/
}
