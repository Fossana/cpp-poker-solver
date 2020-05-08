#ifndef CARD_H_
#define CARD_H_

#include "RankEnum.h"
#include "SuitEnum.h"
#include "HashUtils.h"
#include <cstdint>

class Card
{
public:
	static constexpr uint8_t ENCODED_CARD_FIRST = 1;
	static constexpr uint8_t ENCODED_CARD_LAST = 52;

	Card();
	explicit Card(const std::string& str);
	explicit Card(const Rank rank, const Suit suit);
	explicit Card(const uint8_t code);
	Card(const Card& other);
	Card& operator=(const Card& other);

	bool operator==(const Card& other) const;
	bool operator!=(const Card& other) const;

	inline uint8_t code() const
	{
		return code_;
	}

	std::string toString() const;
	Rank rank() const;
	Suit suit() const;

private:
	uint8_t code_;
};

MAKE_HASHABLE(Card, t.code())

#endif // CARD_H_