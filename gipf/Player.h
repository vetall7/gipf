#pragma once

class Player {
private:
	int stones;
	int reserve_stones;
public:
	void SetStones(int stones);
	int GetStones();
	void SetReserveStones(int stones);
	int GetReserveStones();
	Player(int stones, int reserve_stones);
	Player() = default;
};

