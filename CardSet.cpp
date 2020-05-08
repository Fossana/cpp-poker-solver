#include "CardSet.h"

CardSet::CardSet():
	cardMask_(0)
{
}

CardSet::CardSet(const Card& card) :
	cardMask_(0)
{
	Insert(card);
}

CardSet::CardSet(const CardSet& other):
	cardMask_(other.cardMask_)
{
}

CardSet::CardSet(const uint64_t cardMask) :
	cardMask_(cardMask)
{
}

std::vector<Card> CardSet::cards() const
{
	std::vector<Card> retval;
	retval.reserve(size());

	for (uint8_t encodedCard = Card::ENCODED_CARD_FIRST; encodedCard <= Card::ENCODED_CARD_LAST; ++encodedCard)
	{
		Card card(encodedCard);
		if (Contains(card))
		{
			retval.push_back(card);
		}
	}

	return retval;
}

CardSet CardSet::operator|(const CardSet& other) const
{
	return CardSet(cardMask_ | other.cardMask_);
}

CardSet& CardSet::operator|=(const CardSet& other)
{
	cardMask_ |= other.cardMask_;
	return *this;
}

bool CardSet::operator==(const CardSet& other) const
{
	return cardMask_ == other.cardMask_;
}

bool CardSet::operator!=(const CardSet& other) const
{
	return !(*this == other);
}

bool AreDisjoint(const CardSet& lhs, const CardSet& rhs)
{
	return (lhs.cardMask_ & rhs.cardMask_) == 0;
}

bool CardSet::Contains(const Card& card) const
{
	uint64_t bit = 1i64 << card.code();
	return ((bit & cardMask_) != 0);
}

bool DoIntersect(const CardSet& lhs, const CardSet& rhs)
{
	return !AreDisjoint(lhs, rhs);
}

void CardSet::Insert(const Card& card)
{
	cardMask_ |= (1i64 << card.code());
}

void CardSet::Remove(const Card& card)
{
	cardMask_ ^= 1i64 << card.code();
}

/*
 * Uses Brian Kernighan's algorithm.
 */
size_t CardSet::size() const
{
	uint64_t n = cardMask_;
	size_t count = 0;
	while (n)
	{
		n &= (n - 1);
		++count;
	}
	return count;
}