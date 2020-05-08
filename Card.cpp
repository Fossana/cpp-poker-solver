#include "Card.h"

Card::Card():
	code_(0)
{
}

Card::Card(const std::string& str)
{
	char rankChar = str.at(0);
	char suitChar = str.at(1);

	Rank rank = RankFromChar(rankChar);
	Suit suit = SuitFromChar(suitChar);

	code_ = rank * 4 + suit;
}

Card::Card(const Rank rank, const Suit suit):
	code_(rank * 4 + suit)
{
}

Card::Card(const uint8_t code):
	code_(code)
{
}

Card::Card(const Card& other):
	code_(other.code_)
{
}

Card& Card::operator=(const Card& other)
{
	code_ = other.code_;
	return *this;
}

bool Card::operator==(const Card& other) const
{
	return code_ == other.code_;
}

bool Card::operator!=(const Card& other) const
{
	return code_ != other.code_;
}

Rank Card::rank() const
{
	return (Rank) ((code_ - 1) / 4);
}

Suit Card::suit() const
{
	return (Suit) (code_ - rank() * 4);
}

std::string Card::toString() const
{
	std::string retval;

	retval += CharFromRank(rank());
	retval += CharFromSuit(suit());

	return retval;
}