#ifndef RANK_ENUM_H_
#define RANK_ENUM_H_

#include <unordered_map>

enum Rank
{
	TWO = 0,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

const std::unordered_map<char, Rank> charToRank =
{
	{'2', Rank::TWO},
	{'3', Rank::THREE},
	{'4', Rank::FOUR},
	{'5', Rank::FIVE},
	{'6', Rank::SIX},
	{'7', Rank::SEVEN},
	{'8', Rank::EIGHT},
	{'9', Rank::NINE},
	{'T', Rank::TEN},
	{'J', Rank::JACK},
	{'Q', Rank::QUEEN},
	{'K', Rank::KING},
	{'A', Rank::ACE}
};

const std::unordered_map<Rank, char> rankToChar =
{
	{ Rank::TWO, '2' },
	{ Rank::THREE, '3' },
	{ Rank::FOUR, '4' },
	{ Rank::FIVE, '5' },
	{ Rank::SIX, '6' },
	{ Rank::SEVEN, '7' },
	{ Rank::EIGHT, '8' },
	{ Rank::NINE, '9' },
	{ Rank::TEN, 'T' },
	{ Rank::JACK, 'J' },
	{ Rank::QUEEN, 'Q' },
	{ Rank::KING, 'K' },
	{ Rank::ACE, 'A' }
};

Rank RankFromChar(const char ch);
char CharFromRank(const Rank rank);

#endif // RANK_ENUM_H_