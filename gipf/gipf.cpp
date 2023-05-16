#include <iostream>
#include <vector>
using namespace std;

enum class CellState {
    Empty,
    Black, 
    White
};

class Game {

};

int main()
{
    int size, length, white_stones, black_stones;
    cin >> size >> length >> white_stones >> black_stones;
    int white_reserves, black_reserves;
    cin >> white_reserves >> black_reserves;
    char first_player;
    cin >> first_player;
    std::vector<std::vector<char>> array (size*2);
    char zn;
    for (int i = 0; i < size*2; i++) {
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
    }
}
