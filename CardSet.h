#ifndef CARD_SET_H_
#define CARD_SET_H_

#include "Card.h"
#include <vector>

class CardSet
{
public:
	CardSet();
	CardSet(const Card& card);
	CardSet(const CardSet& other);
	CardSet(const uint64_t cardMask);

	CardSet operator|(const CardSet& other) const;
	CardSet& operator|=(const CardSet& other);
	bool operator==(const CardSet& other) const;
	bool operator!=(const CardSet& other) const;
	friend bool AreDisjoint(const CardSet& lhs, const CardSet& rhs);
	friend bool DoIntersect(const CardSet& lhs, const CardSet& rhs);

	inline uint64_t cardMask() const
	{
		return cardMask_;
	}
	std::vector<Card> cards() const;
	size_t size() const;

	void Insert(const Card& card);
	void Remove(const Card& card);
	bool Contains(const Card& card) const;

private:
	uint64_t cardMask_;
};

#endif // CARD_SET_H_