#include "HandDistributionUtils.h"
#include "GameConstants.h"

namespace
{

int CalculateNumberOfPossiblePreflopCombos(const int numCardsRemoved)
{
	return (NUM_CARDS_IN_DECK - numCardsRemoved) * (NUM_CARDS_IN_DECK - numCardsRemoved - 1) / 2;
}

} // anonymous

HandDistribution GenerateUniformHandDistribution(const CardSet& deadCards)
{
	std::vector<Hand> hands;
	hands.reserve(CalculateNumberOfPossiblePreflopCombos(static_cast<int>(deadCards.size())));

	for (uint8_t encodedCard1 = Card::ENCODED_CARD_FIRST; encodedCard1 <= Card::ENCODED_CARD_LAST; ++encodedCard1)
	{
		Card card1(encodedCard1);
		if (deadCards.Contains(card1))
		{
			continue;
		}

		for (uint8_t encodedCard2 = encodedCard1 + 1; encodedCard2 <= Card::ENCODED_CARD_LAST; ++encodedCard2)
		{
			Card card2(encodedCard2);
			if (deadCards.Contains(card2))
			{
				continue;
			}

			hands.emplace_back(card1, card2);
		}
	}

	return HandDistribution(std::move(hands));
}