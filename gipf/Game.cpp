#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game()
{
    game_state = "in_progress";
}

Game::Game(int size, Player& first, Player& second) : WhitePlayer (first), BlackPlayer(second)
{
    board.resize(size);
    game_state = "in_progress";
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
    cout << size << " " << stones_in_line << " " << WhitePlayer.GetStones() << " " << BlackPlayer.GetStones() << endl;
    cout << WhitePlayer.GetReserveStones() << " " << BlackPlayer.GetReserveStones();
    if (is_white_turn) {
        cout << " W" << endl;
    }
    else {
        cout << " B" << endl;
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


bool checkSameElements(const vector<Point>& vector1, const vector<Point>& vector2) {
    if (vector1.size() != vector2.size()) {
        return false;
    }

    auto sortFunc = [](const Point& p1, const Point& p2) {
        if (p1.GetX() < p2.GetX()) {
            return true;
        }
        else if (p1.GetX() == p2.GetX()) {
            return p1.GetY() < p2.GetY();
        }
        return false;
    };

    std::vector<Point> sortedVector1 = vector1;
    std::vector<Point> sortedVector2 = vector2;
    std::sort(sortedVector1.begin(), sortedVector1.end(), sortFunc);
    std::sort(sortedVector2.begin(), sortedVector2.end(), sortFunc);

    return std::equal(sortedVector1.begin(), sortedVector1.end(), sortedVector2.begin());
}


void SortVector(vector<Point>& vec) {
    auto sortFunc = [](const Point& p1, const Point& p2) {
        if (p1.GetX() < p2.GetX()) {
            return true;
        }
        else if (p1.GetX() == p2.GetX()) {
            return p1.GetY() < p2.GetY();
        }
        return false;
    };

    std::sort(vec.begin(), vec.end(), sortFunc);
}


bool Game::BoardCheck()
{
    int temp = size;
    int k = 0;
    for (vector<CellState> i : board) {
        int counter = 0;
        for (CellState j : i) {
            if (j != CellState::Space) {
                counter++;
            }
        }
        if (counter != temp) {
            return false;
        }
        if (k < size - 1) {
            temp++;
        }
        else {
            temp--;
        }
        k++;
    }
    return true;
}


int Game::isNoDeletedLines()
{
    vector<vector<Point>> board_copy;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != CellState::Space) {
                vector<Point> temp_left;
                vector<Point> temp_right;
                vector<Point> temp_hor;
                Point k(j, i);
                if (board[i][j] == CellState::White || board[i][j] == CellState::Black) {
                    temp_left.push_back(k);
                    temp_right.push_back(k);
                    temp_hor.push_back(k);
                }
                CheckLeftLine(temp_left, k);
                CheckRightLine(temp_right, k);
                CheckHorizontalLine(temp_hor, k);
                if (temp_left.size() >= stones_in_line) {
                    board_copy.push_back(temp_left);
                }
                if (temp_right.size() >= stones_in_line) {
                    board_copy.push_back(temp_right);
                }
                if (temp_hor.size() >= stones_in_line) {
                    board_copy.push_back(temp_hor);
                }
            }
        }
    }
    int counter = 0;
    int i = 0;
    while (i < board_copy.size()) {
        int j = i + 1;
        while (j < board_copy.size()) {
            if (checkSameElements(board_copy[i], board_copy[j])) {
                board_copy.erase(board_copy.begin() + j);
            }
            else {
                j++;
            }
        }
        i++;
    }

    for (vector<Point> i : board_copy) {
        if (IsLine(i)) {
            counter++;
        }
    }
    return counter;
}


void Game::ReadBoard(int size)
{
    char zn;
    int i = 0, j = 0;
    zn = getchar();
    int black_counter = 0, white_counter = 0;
    char e = zn;
    while (i != size * 2 - 1) {
        zn = getchar();
        if (zn == '\n') {
            if (j <= size * 3) {
                while (j != size * 3 + 1) {
                    SetCell(j, i, CellState::Space);
                    j++;
                }
            }
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
        e = zn;
        if (zn == EOF){
            break;
        }
    }
    int count = isNoDeletedLines();
    if (count != 0){
        if (count == 1) {
            cout << "ERROR_FOUND_" << count << "_ROW_OF_LENGTH_K" << endl;
        }
        else {
            cout << "ERROR_FOUND_" << count << "_ROWS_OF_LENGTH_K" << endl;
        }
    }
    else if (white_counter + WhitePlayer.GetReserveStones() != WhitePlayer.GetStones()) {
        cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
        for (auto& innerVector : board) {
            innerVector.clear();
        }
        board.clear();
        board.resize(0);
    }
    else if (black_counter + BlackPlayer.GetReserveStones() != BlackPlayer.GetStones()) {
        cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
        for (auto& innerVector : board) {
            innerVector.clear();
        }
        board.clear();
        board.resize(0);
    }
    else if (!BoardCheck()) {
        cout << "WRONG_BOARD_ROW_LENGTH" << endl;
    }
    else {
        cout << "BOARD_STATE_OK" << endl;
    }
    if (e == EOF) {
        exit(0);
    }

    AllMoves();
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

void Game::SetStoneLine(int stones)
{
    stones_in_line = stones;
}

int Game::GetSize()
{
    return size;
}


bool Game::Transfer(int x, int y, vector<Point>& line, bool is_just_checking)
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
    line.push_back(Point(x_temp, y_temp));
    while (board[y_temp][x_temp] != CellState::Empty) {
        x_temp += rangeX;
        y_temp += rangeY;
        if (y_temp < 0 || y_temp >= board.size() || x_temp < 0 || x_temp >= board[y_temp].size() || board[y_temp][x_temp] == CellState::Space) {
            game_state = "bad_move";
            is_turn_committed = false;
            cout << "BAD_MOVE_ROW_IS_FULL" << endl;
            return 0;
        }
        line.push_back(Point(x_temp, y_temp));
    }
    while (x_temp != x && !is_just_checking) {
        board[y_temp][x_temp] = board[y_temp - rangeY][x_temp - rangeX];
        x_temp -= rangeX;
        y_temp -= rangeY;
    }
    return 1;
}

bool Game::IsLine(vector<Point>& line)
{
    if (line.size() >= stones_in_line) {
        for (int i = 0; i < line.size(); i++) {
            int counter = 1;
            for (int j = i+1; j < i+stones_in_line; j++) {
                if (j < line.size() && board[line[i].GetY()][line[i].GetX()] == board[line[j].GetY()][line[j].GetX()]) {
                    counter++;
                }
                else {
                    break;
                }
            }
            if (counter >= stones_in_line) {
                return true;
            }
        }
    }
    return false;
}

void Game::CheckLeftLine(vector<Point>& line_left, Point& i)
{
    int y_temp = i.GetY(), x_temp = i.GetX();
    while (y_temp >= 0 && x_temp >= 0 && board[y_temp][x_temp] != CellState::Empty && board[y_temp][x_temp] != CellState::Space) {
        y_temp--;
        x_temp--;
    }
    y_temp++;
    x_temp++;
    while (y_temp < board.size() && x_temp < board[0].size() && board[y_temp][x_temp] != CellState::Empty && board[y_temp][x_temp] != CellState::Space) {
        Point temp(x_temp, y_temp);
        if (!(temp == i)) {
            line_left.push_back(Point(x_temp, y_temp));
        }
        y_temp++;
        x_temp++;
    }
}

void Game::CheckRightLine( vector<Point>& line_right, Point& i)
{
    int y_temp = i.GetY(), x_temp = i.GetX();
    while (y_temp >= 0 && x_temp < board[0].size() && board[y_temp][x_temp] != CellState::Empty && board[y_temp][x_temp] != CellState::Space) {
        y_temp--;
        x_temp++;
    }
    x_temp--;
    y_temp++;
    while (y_temp < board.size() && x_temp >= 0 && board[y_temp][x_temp] != CellState::Empty && board[y_temp][x_temp] != CellState::Space) {
        Point temp(x_temp, y_temp);
        if (!(temp == i)) {
            line_right.push_back(Point(x_temp, y_temp));
        }
        y_temp++;
        x_temp--;
    }
}

void Game::CheckHorizontalLine(vector<Point>& horizontal_line, Point& i)
{
    int y_temp = i.GetY(), x_temp = i.GetX();
    while (x_temp >= 0 && board[y_temp][x_temp] != CellState::Empty && board[y_temp][x_temp] != CellState::Space) {
        x_temp -= 2;
    }
    x_temp += 2;
    while (x_temp < board[y_temp].size() && board[y_temp][x_temp] != CellState::Empty && board[y_temp][x_temp] != CellState::Space) {
        Point temp(x_temp, y_temp);
        if (!(temp == i)) {
            horizontal_line.push_back(Point(x_temp, y_temp));
        }
        x_temp += 2;
    }
}


void Game::Move(int x, int y, vector<vector<Point>>& to_delete)
{
    vector <Point> line;
    line.push_back(Point(x, y));
    game_state = "in_progress";
    if (board[y][x] != CellState::Empty) {
        Transfer(x, y, line, 0);
    }
    size_t found = game_state.find("bad_move");
    if (is_white_turn && found == std::string::npos) {
        board[y][x] = CellState::White;
        is_white_turn = false;
        WhitePlayer.StonesDecrease(1);
    }
    else if (found == std::string::npos) {
        board[y][x] = CellState::Black;
        is_white_turn = true;
        BlackPlayer.StonesDecrease(1);
    }
    vector<vector<Point>> lines_to_delete;
    bool is_checked = false;
    for (Point i : line) {
        vector<Point> line_left;
        vector<Point> line_right;
        vector<Point> line_horizontal;
        line_left.push_back(Point(i.GetX(), i.GetY()));
        line_horizontal.push_back(Point(i.GetX(), i.GetY()));
        line_right.push_back(Point(i.GetX(), i.GetY()));
        if (direction == Right || direction == Left) {
            if (!is_checked) {
                CheckHorizontalLine(line_horizontal, i);
            }
            CheckLeftLine(line_left, i);
            CheckRightLine(line_right, i);
            SortVector(line_horizontal);
            SortVector(line_left);
            SortVector(line_right);
            if (IsLine(line_left)) {
                lines_to_delete.push_back(line_left);
            }
            if (IsLine(line_right)) {
                lines_to_delete.push_back(line_right);
            }
            if (IsLine(line_horizontal)) {
                lines_to_delete.push_back(line_horizontal);
                is_checked = true;
            }
        }
        else if (direction == RightDown || direction == LeftUp) {
            if (!is_checked) {
                CheckLeftLine(line_horizontal, i);
            }
            CheckHorizontalLine(line_left, i);
            CheckRightLine(line_right, i);
            SortVector(line_horizontal);
            SortVector(line_left);
            SortVector(line_right);
            if (IsLine(line_left)) {
                lines_to_delete.push_back(line_left);
            }
            if (IsLine(line_right)) {
                lines_to_delete.push_back(line_right);
            }
            if (IsLine(line_horizontal)) {
                lines_to_delete.push_back(line_horizontal);
                is_checked = true;
            }
        }
        else if (direction == LeftDown || direction == RightUp) {
            if (!is_checked) {
                CheckRightLine(line_horizontal, i);
            }
            CheckHorizontalLine(line_right, i);
            CheckLeftLine(line_left, i);
            SortVector(line_horizontal);
            SortVector(line_left);
            SortVector(line_right);
            if (IsLine(line_left)) {
                lines_to_delete.push_back(line_left);
            }
            if (IsLine(line_right)) {
                lines_to_delete.push_back(line_right);
            }
            if (IsLine(line_horizontal)) {
                lines_to_delete.push_back(line_horizontal);
                is_checked = true;
            }
        }
    }
    
    if (lines_to_delete.size() == 1) {
        int white_counter = 0, black_counter = 0;
        for (Point i : lines_to_delete[0]) {
            if (board[i.GetY()][i.GetX()] == CellState::White) {
                white_counter++;
            }
            else {
                black_counter++;
            }
            board[i.GetY()][i.GetX()] = CellState::Empty;
        }
        if (white_counter > black_counter) {
            WhitePlayer.StonesIncrease(white_counter);
        }
        else {
            BlackPlayer.StonesIncrease(black_counter);
        }
    }
    else if (lines_to_delete.size() != 0 && to_delete.size() == 0) {
        for (vector<Point> i : lines_to_delete) {
            int white_counter = 0, black_counter = 0;
            for (Point j : i) {
                if (board[j.GetY()][j.GetX()] == CellState::White) {
                    white_counter++;
                }
                else {
                    black_counter++;
                }
                board[j.GetY()][j.GetX()] = CellState::Empty;
            }
            if (white_counter > black_counter) {
                WhitePlayer.StonesIncrease(white_counter);
            }
            else {
                BlackPlayer.StonesIncrease(black_counter);
            }
        }
    }
    else if (lines_to_delete.size() != 0){
        int white_counter = 0, black_counter = 0;
        for (vector<Point> i : lines_to_delete) {
            for (vector<Point> k : to_delete) {
                if (checkSameElements(i, k)) {
                    for (Point j : k) {
                        if (board[j.GetY()][j.GetX()] == CellState::White) {
                            white_counter++;
                        }
                        else {
                            black_counter++;
                        }
                        board[j.GetY()][j.GetX()] = CellState::Empty;
                    }
                    break;
                }
            }
        }
        if (white_counter > black_counter) {
            WhitePlayer.StonesIncrease(white_counter);
        }
        else {
            BlackPlayer.StonesIncrease(black_counter);
        }
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

bool Game::IsGoodField(string coo, bool is_start)
{
    int x, y;
    ConvertCoordinate(coo, x, y);
    if (is_start) {
        if (x < 0 || y < 0 || x >= size*3-1 || y >= size*2-1) {
            return true;
        }
    }
    else {
        if (x < 0 || y < 0) {
            return false;
        }
        return true;
    }
    return false;
}


bool Game::IsGoodCoordinate(string coo, bool is_start)
{
    if (is_start && coo[0] > 'a' + size*2 ) {
        return false;
    }
    else if (!is_start && coo[0] > 'a' + size*2 - 1) {
        return false;
    }
    int index_x = coo[0] - 'a';
    int index_y = coo[1] - '0';
    int max;
    if (index_x <= size) {
        max = index_x + size + 1;
    }
    else {
        int max_from_size =  index_x - size;
        max = size + size + 1 - max_from_size;
    }
    if (index_y > max) {
        return false;
    }
    return true;
}


void Game::DoMove(string from, string to, vector<string>& delete_points)
{
    is_turn_committed = false;
    vector<vector<Point>> to_delete;
    int x, y;
    if (delete_points.size() >= stones_in_line) {
        int index = 0;
        vector<Point> current;
        for (string i : delete_points) {
            if (i[1] == ':') {
                to_delete.push_back(current);
                current.clear();
            }
            else {
                ConvertCoordinate(i, x, y);
                current.push_back(Point(x, y));
                if (index == delete_points.size() - 1) {
                    to_delete.push_back(current);
                }
            }
            index++;
        }
    }
    vector<string> coordinates;
    GenerateMoves(coordinates, from);
    for (string i : coordinates) {
        if (i == to) {
            is_turn_committed = true;
        }
    }

    if (!IsGoodCoordinate(from, true)) {
        cout << "BAD_MOVE_" << from << "_IS_WRONG_INDEX" << endl;
        return;
    }
    else if (!IsGoodCoordinate(to, false)) {
        cout << "BAD_MOVE_" << to << "_IS_WRONG_INDEX" << endl;
        return;
    }
    if (!IsGoodField(from, true)) {
        cout << "BAD_MOVE_" << from << "_IS_WRONG_STARTING_FIELD" << endl;
        return;
    }else if (!IsGoodField(to, false)) {
        cout << "BAD_MOVE_" << to << "_IS_WRONG_DESTINATION_FIELD" << endl;
        return;
    }

    if (is_turn_committed) {
        int x_to, y_to;
        ConvertCoordinate(to, x_to, y_to);
        DirectionDetect(from, to);
        Move(x_to, y_to, to_delete);
        x = x_to, y = y_to;
        if (is_turn_committed) {
            cout << "MOVE_COMMITTED" << endl;
        }
    }
    else {
        cout << "UNKNOWN_MOVE_DIRECTION" << endl;
        game_state = "bad_move";
    }
    if (WhitePlayer.GetReserveStones() == 0 && is_white_turn) {
        game_state = "black win";
    }
    else if (BlackPlayer.GetReserveStones() == 0 && !is_white_turn) {
        game_state = "white_win";
    }
    /*if (game_state == "bad_move") {
        if (board[y][x] == CellState::White) {
            game_state += " <white> ";
        }
        else if (board[y][x] == CellState::Black) {
            game_state += " <black> ";
        }
        game_state += "<" + from + "-" + to + ">";
    }*/
}

void Game::SetTurn(bool turn)
{
    is_white_turn = turn;
}

void Game::PrintState()
{
    cout << game_state << endl;
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
    int max = (size * 2 + 1) - (index_x - size); // ������������ ����� ������� ����� ����� �����
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


void Game::AllMoves()
{
    vector<string> coordinates_from;
    vector<string> coordinates_to;
    int max_point = size * 2;
    while (max_point != -1) {
        int max;
        if (max_point <= size) {
            max = max_point + size + 1;
        }
        else {
            int max_from_size = max_point - size;
            max = size + size + 1 - max_from_size;
        }
        vector<string> moves_max;
        vector<string> moves_min;
        string coo_max = (char)('a' + max_point) + to_string(max);
        string coo_min = (char)('a' + max_point) + to_string(1);
        GenerateMoves(moves_max, coo_max);
        for (string i : moves_max) {
            DirectionDetect(coo_max, i);
            int x_to, y_to;
            ConvertCoordinate(i, x_to, y_to);
            vector<Point> line;
            if (!Transfer(x_to, y_to, line, 1)) {
                continue;
            }
            else {
                coordinates_to.push_back(i);
            }
        }
        GenerateMoves(moves_min, coo_min);
        for (string i : moves_min) {
            DirectionDetect(coo_min, i);
            int x_to, y_to;
            ConvertCoordinate(i, x_to, y_to);
            vector<Point> line;
            if (!Transfer(x_to, y_to, line, 1)) {
                continue;
            }
            else {
                coordinates_to.push_back(i);
            }
        }
        if (max_point == size * 2 || max_point == 0) {
            vector<string> avarage;
            int temp = max-1;
            while (temp != 1) {
                string coo = (char)('a' + max_point) + to_string(temp);
                GenerateMoves(avarage, coo);
                for (string i : avarage) {
                    DirectionDetect(coo, i);
                    int x_to, y_to;
                    ConvertCoordinate(i, x_to, y_to);
                    vector<Point> line;
                    if (!Transfer(x_to, y_to, line, 1)) {
                        continue;
                    }
                    else {
                        coordinates_to.push_back(i);
                    }
                }
                temp--;
            }
        }
        max_point--;
    }
    int i = 0;
    while (i < coordinates_to.size()) {
        int j = i + 1;
        int counter = 0;
        while (j < coordinates_to.size()) {
            if (coordinates_to[i] == coordinates_to[j]) {
                counter++;
                int x_temp, y_temp;
                ConvertCoordinate(coordinates_to[j], x_temp, y_temp);
                if (board[y_temp][x_temp] == CellState::Empty || counter >=3) {
                    coordinates_to.erase(coordinates_to.begin() + j);
                }
                else {
                    j++;
                }
            }
            else {
                j++;
            }
        }
        i++;
    }

    cout << coordinates_to.size() << endl;
    for (string i : coordinates_to) {
        cout << i << endl;
    }
}
