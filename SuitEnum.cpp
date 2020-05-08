#include "SuitEnum.h"

Suit SuitFromChar(const char ch)
{
	return charToSuit.at(ch);
}

char CharFromSuit(const Suit suit)
{
	return suitToChar.at(suit);
}