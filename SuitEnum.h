#ifndef SUIT_ENUM_H_
#define SUIT_ENUM_H_

#include <unordered_map>

enum Suit
{
	CLUBS = 1,
	DIAMONDS,
	HEARTS,
	SPADES
};

const Suit suits[] = { Suit::CLUBS, Suit::DIAMONDS, Suit::HEARTS, Suit::SPADES };

const std::unordered_map<char, Suit> charToSuit =
{
	{'c', Suit::CLUBS},
	{'d', Suit::DIAMONDS},
	{'h', Suit::HEARTS},
	{'s', Suit::SPADES}
};

const std::unordered_map<Suit, char> suitToChar =
{
	{ Suit::CLUBS, 'c' },
	{ Suit::DIAMONDS, 'd' },
	{ Suit::HEARTS, 'h' },
	{ Suit::SPADES, 's' }
};

Suit SuitFromChar(const char ch);
char CharFromSuit(const Suit suit);

#endif // SUIT_ENUM_H_