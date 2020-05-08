#include "Board.h"
#include <iterator>

Board::Board(const Card flop1, const Card flop2, const Card flop3)
{
	cards_[0] = flop1;
	cards_[1] = flop2;
	cards_[2] = flop3;

	size_ = 3;
}

Board::Board(const Card flop1, const Card flop2, const Card flop3, const Card turn)
{
	cards_[0] = flop1;
	cards_[1] = flop2;
	cards_[2] = flop3;
	cards_[3] = turn;

	size_ = 4;
}

Board::Board(const Card flop1, const Card flop2, const Card flop3, const Card turn, const Card river)
{
	cards_[0] = flop1;
	cards_[1] = flop2;
	cards_[2] = flop3;
	cards_[3] = turn;
	cards_[4] = river;

	size_ = 5;
}

Board::Board(const Board& other)
{
	for (std::size_t i = 0; i < other.size_; ++i)
	{
		cards_[i] = other.cards_[i];
	}

	size_ = other.size_;
}

const Card& Board::operator[] (const int index) const
{
	return cards_[index];
}

const Card* Board::begin() const
{
	return &cards_[0];
}

const Card* Board::end() const
{
	return &cards_[size_];
}

Card* Board::begin()
{
	return &cards_[0];
}

Card* Board::end()
{
	return &cards_[size_];
}

bool Board::Contains(const Card card) const
{
	bool retval = false;

	for (int i = 0; i < size_; ++i)
	{
		if (cards_[i] == card)
		{
			retval = true;
			break;
		}
	}

	return retval;
}

const bool Board::operator==(const Board& other) const
{
	bool retval = true;

	if (size_ != other.size_)
	{
		retval = false;
	}
	else
	{
		for (int i = 0; i < size_; ++i)
		{
			if (cards_[i] != other.cards_[i])
			{
				retval = false;
				break;
			}
		}
	}

	return retval;
}

Street Board::GetStreet() const
{
	switch (static_cast<int>(size_))
	{
		case 3:
			return Street::FLOP;
		case 4:
			return Street::TURN;
		case 5:
			return Street::RIVER;
	}
}

void Board::Add(const Card card)
{
	cards_[size_++] = card;
}