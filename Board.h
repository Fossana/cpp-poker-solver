#ifndef BOARD_H_
#define BOARD_H_

#include "Card.h"
#include "StreetEnum.h"
#include <vector>
#include <cstddef>

enum class BoardIndex
{
	FLOP_ONE = 0,
	FLOP_TWO = 1,
	FLOP_THREE = 2,
	TURN = 4,
	RIVER = 5
};

class Board
{
public:
	Board(const Card flop1, const Card flop2, const Card flop3);
	Board(const Card flop1, const Card flop2, const Card flop3, const Card turn);
	Board(const Card flop1, const Card flop2, const Card flop3, const Card turn, const Card river);
	Board(const Board& other);

	const bool operator==(const Board& other) const;
	const Card& operator[] (const int index) const;

	const Card* begin() const;
	const Card* end() const;
	Card* begin();
	Card* end();

	inline std::size_t size() const
	{
		return size_;
	}

	inline const Card* cards() const
	{
		return cards_;
	}

	inline Card* cards()
	{
		return cards_;
	}

	bool Contains(const Card card) const;
	void Add(const Card card);
	Street GetStreet() const;

private:
	Card cards_[5];
	std::size_t size_;
};

namespace std
{

template<> struct hash<Board> {
	std::size_t operator()(const Board &board) const
	{
		std::size_t retval = 0;
		for (const Card& card : board)
		{
			hash_combine(retval, card);
		}
		return retval;
	}
};

} // std

#endif // BOARD_H_