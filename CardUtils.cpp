#include "CardUtils.h"

namespace CardUtils
{

Card CardFromString(const std::string& str)
{
	char rankChar = str.at(0);
	char suitChar = str.at(1);

	return CardFromRankAndSuit(RankFromChar(rankChar), SuitFromChar(suitChar));
}

Card CardFromRankAndSuit(Rank rank, Suit suit)
{
	return rank * 4 + suit;
}

Rank GetRank(Card card)
{
	return (Rank) (card / 4);
}

Suit GetSuit(Card card)
{
	Rank rank = GetRank(card);
	return (Suit) (card - rank * 4);
}

}