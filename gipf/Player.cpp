#include "Player.h"

void Player::SetStones(int stones)
{
	this->stones = stones;
}

int Player::GetStones()
{
	return stones;
}

void Player::SetReserveStones(int stones)
{
	this->reserve_stones = stones;
}

int Player::GetReserveStones()
{
	return reserve_stones;
}

Player::Player(int stones, int reserve_stones) : stones(stones), reserve_stones(reserve_stones)
{

}
