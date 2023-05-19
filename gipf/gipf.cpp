#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Game.h"
using namespace std;

void read_command(string &command, Game& game){
    if (command == "LOAD_GAME_BOARD") {
        int size, length, white_stones, black_stones;
        cin >> size >> length >> white_stones >> black_stones;
        int white_reserves, black_reserves;
        cin >> white_reserves >> black_reserves;
        char first_player;
        cin >> first_player;
        Player white(white_stones, white_reserves);
        Player black(black_stones, black_reserves);
        game.SetPlayers(white, black);
        game.SetSize(size);
        game.ReadBoard(game.GetSize());
    }
    else if (command == "PRINT_GAME_BOARD") {
        system("cls");
        game.DrawWorld();
    }
    else {
        cout << "NO COMMAND" << endl;
    }
}

int main()
{
    Game game;
    while (1) {
        string command;
        cin >> command;
        read_command(command, game);
    }
}
