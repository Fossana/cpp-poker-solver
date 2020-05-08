#include "Hand.h"

Hand::Hand(const Card card1, const Card card2, const double weight):
	card1_(card1),
	card2_(card2),
	weight_(weight)
{
}

bool Hand::operator==(const Hand& other) const
{
	return	card1_ == other.card1_ &&
			card2_ == other.card2_ &&
			weight_ == other.weight_;
}