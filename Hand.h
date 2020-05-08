#ifndef HAND_H_
#define HAND_H_

#include "Card.h"

class Hand
{
public:
	Hand(const Card card1, const Card card2, const double weight = 1.0);

	bool operator==(const Hand& other) const;

	inline Card card1() const
	{
		return card1_;
	}

	inline Card card2() const
	{
		return card2_;
	}

	inline double weight() const
	{
		return weight_;
	}

private:
	Card card1_;
	Card card2_;
	double weight_;
};

MAKE_HASHABLE(Hand, t.card1(), t.card2(), t.weight())

#endif // HAND_H_