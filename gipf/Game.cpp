#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game()
{
    game_state = "in_progress";
}

Game::Game(int size, Player& first, Player& second) : WhitePlayer(first), BlackPlayer(second)
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
        if (zn == EOF) {
            break;
        }
    }
    if (!BoardCheck()) {
        cout << "WRONG_BOARD_ROW_LENGTH" << endl;
        board.clear();
        return;
    }
    else if (1) {
        int count = isNoDeletedLines();
        if (count == 1) {
            cout << "ERROR_FOUND_" << count << "_ROW_OF_LENGTH_K" << endl;
            board.clear();
            return;
        }
        else if (count != 0) {
            cout << "ERROR_FOUND_" << count << "_ROWS_OF_LENGTH_K" << endl;
            board.clear();
            return;
        }
    }
    if (white_counter + WhitePlayer.GetReserveStones() > WhitePlayer.GetStones()) {
        cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
        for (auto& innerVector : board) {
            innerVector.clear();
        }
        board.clear();
        board.resize(0);
    }
    else if (black_counter + BlackPlayer.GetReserveStones() > BlackPlayer.GetStones()) {
        cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
        for (auto& innerVector : board) {
            innerVector.clear();
        }
        board.clear();
        board.resize(0);
    }
    else {
        cout << "BOARD_STATE_OK" << endl;
    }
    if (e == EOF) {
        exit(0);
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

void Game::SetStoneLine(int stones)
{
    stones_in_line = stones;
}

int Game::GetSize()
{
    return size;
}


void Game::Transfer(int x, int y, vector<Point>& line, bool is_just_checking)
{
    int rangeX = 0, rangeY = 0;
    if (direction == Right) {
        rangeX = 2;
    }
    else if (direction == Left) {
        rangeX = -2;
    }
    else if (direction == RightDown) {
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
            if (!is_just_checking) cout << "BAD_MOVE_ROW_IS_FULL" << endl;
            return;
        }
        line.push_back(Point(x_temp, y_temp));
    }
    while (x_temp != x) {
        board[y_temp][x_temp] = board[y_temp - rangeY][x_temp - rangeX];
        x_temp -= rangeX;
        y_temp -= rangeY;
    }
}

bool Game::IsLine(vector<Point>& line)
{
    if (line.size() >= stones_in_line) {
        for (int i = 0; i < line.size(); i++) {
            int counter = 1;
            for (int j = i + 1; j < i + stones_in_line; j++) {
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

void Game::CheckRightLine(vector<Point>& line_right, Point& i)
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


void Game::Move(int x, int y, vector<vector<Point>>& to_delete, bool is_test_move)
{
    vector <Point> line;
    line.push_back(Point(x, y));
    game_state = "in_progress";
    if (board[y][x] != CellState::Empty) {
        if (!is_test_move) Transfer(x, y, line, 0);
        else Transfer(x, y, line, 1);
    }
    size_t found = game_state.find("bad_move");
    if (is_white_turn && found == std::string::npos) {
        board[y][x] = CellState::White;
        if (!is_test_move) {
            is_white_turn = false;
        }
        WhitePlayer.StonesDecrease(1);
    }
    else if (found == std::string::npos) {
        board[y][x] = CellState::Black;
        if (!is_test_move) {
            is_white_turn = true;
        }
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
            //checkSameElements(line_left, line_right);
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
    DeleteStones(to_delete, lines_to_delete);
}


void Game::DeleteStones(vector<vector<Point>>& to_delete, vector<vector<Point>>& lines_to_delete)
{
    is_good_index = true;
    is_good_color = true;
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
    else if (lines_to_delete.size() != 0) {
        for (vector<Point> k : to_delete) {
            if (k.size() != 2) {
                continue;
            }
            int white_counter = 0, black_counter = 0;
            int x_diff = k[0].GetX() - k[1].GetX(), y_diff = k[0].GetY() - k[1].GetY();
            if (x_diff < 0) x_diff *= -1;
            if (y_diff < 0) y_diff *= -1;
            if (x_diff / 2 >= stones_in_line - 1 || y_diff >= stones_in_line - 1) {
                for (vector<Point> i : lines_to_delete) {
                    auto is_from = std::find(i.begin(), i.end(), k[0]);
                    auto is_to = std::find(i.begin(), i.end(), k[1]);
                    if (is_from != i.end() && is_to != i.end()) {
                        for (Point j : i) {
                            if (board[j.GetY()][j.GetX()] == CellState::White) {
                                white_counter++;
                            }
                            else {
                                black_counter++;
                            }
                        }
                        if (white_counter > black_counter && WhoTakes == CellState::White) {
                            WhitePlayer.StonesIncrease(white_counter);
                        }
                        else if (white_counter < black_counter && WhoTakes == CellState::Black) {
                            BlackPlayer.StonesIncrease(black_counter);
                        }
                        else {
                            is_good_color = false;
                        }
                        if (is_good_color) {
                            for (Point j : i) {
                                board[j.GetY()][j.GetX()] = CellState::Empty;
                            }
                        }
                    }
                }
            }
            else {
                is_good_index = false;
            }
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
        if (x < 0 || y < 0 || x >= size * 3 - 1 || y >= size * 2 - 1) {
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
    if (is_start && coo[0] > 'a' + size * 2) {
        return false;
    }
    else if (!is_start && coo[0] > 'a' + size * 2 - 1) {
        return false;
    }
    int index_x = coo[0] - 'a';
    int index_y = coo[1] - '0';
    int max;
    if (index_x <= size) {
        max = index_x + size + 1;
    }
    else {
        int max_from_size = index_x - size;
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
    if (delete_points.size() == 3) {
        if (delete_points[0] == "w:") {
            WhoTakes = CellState::White;
        }
        else {
            WhoTakes = CellState::Black;
        }
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
    }
    else if (!IsGoodField(to, false)) {
        cout << "BAD_MOVE_" << to << "_IS_WRONG_DESTINATION_FIELD" << endl;
        return;
    }

    if (is_turn_committed) {
        int x_to, y_to;
        ConvertCoordinate(to, x_to, y_to);
        DirectionDetect(from, to);
        Move(x_to, y_to, to_delete, 0);
        x = x_to, y = y_to;
        if (is_turn_committed) {
            if (!is_good_index) {
                cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
            }
            else if (!is_good_color) {
                cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
            }
            else {
                cout << "MOVE_COMMITTED" << endl;
            }
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

void Game::SetWhoTakes(CellState player)
{
    WhoTakes = player;
}

void Game::ConvertCoordinate(string coo, int& x, int& y)
{
    int index_x = coo[0] - 'b';
    int index_y = coo[1] - '0';
    int array_index_x = size - 1 + index_x * 2;
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
    int max = (size * 2 + 1) - (index_x - size); // максимальное число которое может иметь буква
    if (index_y == 1 && index_x >= size) {
        if (index_x == size) {
            coordinates.push_back(string(1, from[0]) + "2");
        }
        else if (index_x == size * 2) {
            coordinates.push_back(string(1, from[0] - 1) + "2");
        }
        else {
            coordinates.push_back(string(1, from[0]) + "2");
            coordinates.push_back(string(1, from[0] - 1) + "2");
        }
    }
    else if (index_y == 1) {
        if (index_x == 0) {
            coordinates.push_back(string(1, from[0] + 1) + "2");
        }
        else {
            coordinates.push_back(string(1, from[0]) + "2");
            coordinates.push_back(string(1, from[0] + 1) + "2");
        }
    }
    else if (from[0] == 'a') {
        if (index_y == size + 1) {
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
        coordinates.push_back(string(1, from[0] - 1) + to_string(index_y));
        coordinates.push_back(string(1, from[0]) + to_string(index_y - 1));
    }
}

void Game::WinMove(bool is_print_all, bool is_print1) {
    if (BlackPlayer.GetReserveStones() != 1) {
        return;
    }
    vector<string> coordinates = AllMoves();
    vector<string> win_moves;
    bool turn = is_white_turn;
    for (string i : coordinates) {
        string from, to;
        from = i.substr(0, 2);
        to = i.substr(3, 4);
        DirectionDetect(from, to);
        int x_to, y_to;
        ConvertCoordinate(to, x_to, y_to);
        vector<vector<Point>> to2;
        vector<vector<CellState>> board_copy = board;
        Move(x_to, y_to, to2, 1);
        if (is_white_turn) is_white_turn = false;
        else is_white_turn = true;
        vector<string> second_turn = AllMoves();
        bool is = true;
        for (string j : second_turn) {
            int white_res = WhitePlayer.GetReserveStones(), black_res = BlackPlayer.GetReserveStones();
            string from1, to1;
            from1 = j.substr(0, 2);
            to1 = j.substr(3, 4);
            DirectionDetect(from1, to1);
            int x_to, y_to;
            ConvertCoordinate(to1, x_to, y_to);
            vector<vector<CellState>> board_copy2 = board;
            Move(x_to, y_to, to2, 1);
            if (BlackPlayer.GetReserveStones() != 0) {
                is = false;
                break;
            }
            board = board_copy2;
            WhitePlayer.SetReserveStones(white_res);
            BlackPlayer.SetReserveStones(black_res);
        }
        if (is_white_turn) is_white_turn = false;
        else is_white_turn = true;
        if (is) {
            string move = from + "-" + to;
            win_moves.push_back(move);
        }
        board = board_copy;
    }
    is_white_turn = turn;
    if (is_print1 && win_moves.size() != 0) {
        cout << "1" << endl;
    }
    else if (is_print_all) {
        cout << win_moves.size() << endl;
    }
    else if (win_moves.size() != 0) {
        cout << win_moves[0] << endl;
    }
    else {
        cout << coordinates.size() << endl;
    }
}

vector<string> Game::AllMoves()
{
    bool static is_check_next_move = true;
    vector<string> coordinates;
    vector<string> coordinates_to;
    vector<vector<vector<CellState>>> all_boards;
    vector<string> winning_moves;
    string state_copy = game_state;
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
            int white_res = WhitePlayer.GetReserveStones(), black_res = BlackPlayer.GetReserveStones();
            DirectionDetect(coo_max, i);
            int x_to, y_to;
            ConvertCoordinate(i, x_to, y_to);
            vector<Point> line;
            vector<vector<Point>> to;
            vector<vector<CellState>> board_copy = board;
            Move(x_to, y_to, to, 1);
            bool is_add = true;
            for (vector<vector<CellState>> i : all_boards) {
                if (i == board) {
                    is_add = false;
                }
            }
            size_t found = game_state.find("bad_move");
            if (is_add && found == std::string::npos) {
                string coo = coo_max + "-" + i;
                coordinates.push_back(coo);
                all_boards.push_back(board);
            }
            board = board_copy;
            WhitePlayer.SetReserveStones(white_res);
            BlackPlayer.SetReserveStones(black_res);
        }
        GenerateMoves(moves_min, coo_min);
        for (string i : moves_min) {
            int white_res = WhitePlayer.GetReserveStones(), black_res = BlackPlayer.GetReserveStones();
            DirectionDetect(coo_min, i);
            int x_to, y_to;
            ConvertCoordinate(i, x_to, y_to);
            vector<vector<Point>> to;
            vector<vector<CellState>> board_copy = board;
            Move(x_to, y_to, to, 1);
            bool is_add = true;
            for (vector<vector<CellState>> i : all_boards) {
                if (i == board) {
                    is_add = false;
                }
            }
            size_t found = game_state.find("bad_move");
            if (is_add && found == std::string::npos) {
                string temp = coo_min + "-" + i;
                coordinates.push_back(temp);
                all_boards.push_back(board);
            }
            board = board_copy;
            WhitePlayer.SetReserveStones(white_res); // 
            BlackPlayer.SetReserveStones(black_res);
        }
        if (max_point == size * 2 || max_point == 0) {
            vector<string> avarage;
            int temp = max - 1;
            while (temp != 1) {
                string coo = (char)('a' + max_point) + to_string(temp);
                GenerateMoves(avarage, coo);
                for (string i : avarage) {
                    int white_res = WhitePlayer.GetReserveStones(), black_res = BlackPlayer.GetReserveStones();
                    DirectionDetect(coo, i);
                    int x_to, y_to;
                    ConvertCoordinate(i, x_to, y_to);
                    vector<vector<Point>> to;
                    vector<vector<CellState>> board_copy = board;
                    Move(x_to, y_to, to, 1);
                    bool is_add = true;
                    for (vector<vector<CellState>> i : all_boards) {
                        if (i == board) {
                            is_add = false;
                        }
                    }
                    size_t found = game_state.find("bad_move");
                    if (is_add && found == std::string::npos) {
                        string temp = coo + "-" + i;
                        coordinates.push_back(temp);
                        all_boards.push_back(board);
                    }
                    board = board_copy;
                    WhitePlayer.SetReserveStones(white_res);
                    BlackPlayer.SetReserveStones(black_res);
                }
                temp--;
            }
        }
        max_point--;
    }
    game_state = state_copy;
    return move(coordinates);
}