#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "Game.h"
using namespace std;

void read_command(string& command, Game& game) {
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
        if (first_player == 'W') {
            game.SetTurn(true);
        }
        else {
            game.SetTurn(false);
        }
        game.ReadBoard(game.GetSize());
    }
    else if (command == "PRINT_GAME_BOARD") {
        game.DrawWorld();
    }
    else if (command == "DO_MOVE") {
        string from, to, line;
        char temp = getchar();
        temp = getchar();
        while (temp != ' ' && temp != '\n') {
            line += temp;
            temp = getchar();
        }
        size_t delimiterPos = line.find('-');
        if (delimiterPos != std::string::npos) {
            from = line.substr(0, delimiterPos);
            to = line.substr(delimiterPos + 1);
        }
        string input;
        if (temp != '\n') {
            getline(std::cin, input);
        }
        std::vector<std::string> words;
        std::string currentWord;
        int counter = 0;
        input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
        int i = 0;
        for (char c : input) {
            if (counter == 2) {
                counter = 0;
                if (!currentWord.empty()) {
                    words.push_back(currentWord);
                    currentWord.clear();
                }
            }
            counter++;
            currentWord += c;
            i++;
            if (i == input.size()) {
                if (!currentWord.empty()) {
                    words.push_back(currentWord);
                    currentWord.clear();
                }
            }
        }
        game.DoMove(from, to, words);
    }
    else if (command == "PRINT_GAME_STATE") {
        game.PrintState();
    }
    else if (command == "GEN_ALL_POS_MOV") {
        game.AllMoves(1);
    }
    else if (command == "GEN_ALL_POS_MOV_EXT") {
        game.WinMove(0, 0);
    }
    else if (command == "GEN_ALL_POS_MOV_NUM") {
        cout << game.AllMoves(0).size() << "_UNIQUE_MOVES" << endl;
    }
    else if (command == "GEN_ALL_POS_MOV_EXT_NUM") {
        game.WinMove(1, 1);
    }
    else {
        cout << "NO COMMAND" << endl;
    }
}

int main()
{
    Game game;
    string command;
    while (cin >> command) {
        read_command(command, game);
        if (cin.eof()) {
            break;
        }
    }
    return 0;
}