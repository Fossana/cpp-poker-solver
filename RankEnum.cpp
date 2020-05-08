#include "RankEnum.h"

Rank RankFromChar(const char ch)
{
	return charToRank.at(ch);
}

char CharFromRank(const Rank rank)
{
	return rankToChar.at(rank);
}