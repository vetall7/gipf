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
        game.SetStoneLine(length);
        game.ReadBoard(game.GetSize());
        if (first_player == 'W') {
            game.SetTurn(true);
        }
        else {
            game.SetTurn(false);
        }
    }
    else if (command == "PRINT_GAME_BOARD") {
        game.DrawWorld();
    }
    else if (command == "DO_MOVE") {
        string from, to;
        cin >> from >> to;
        string input;
        getline(std::cin, input);
        std::vector<std::string> words;
        std::string currentWord;
        for (char c : input) {
            if (c == ' ') {
                if (!currentWord.empty()) {
                    words.push_back(currentWord);
                    currentWord.clear();
                }
            }
            else {
                currentWord += c;
            }
        }
        game.DoMove(from, to, words);
        game.DrawWorld();
    }
    else if (command == "PRINT_GAME_STATE") {
        game.PrintState();
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
