#include "HandEvaluator.h"

HandEvaluator::HandEvaluator(FILE* lookupTable)
{
	fread(HR, sizeof(HR), 1, lookupTable);
}

int HandEvaluator::Evaluate_SevenCards(
	const Card& card1,
	const Card& card2,
	const Card& card3,
	const Card& card4,
	const Card& card5,
	const Card& card6,
	const Card& card7
)
{
	int p = HR[53 + card1.code()];
	p = HR[p + card2.code()];
	p = HR[p + card3.code()];
	p = HR[p + card4.code()];
	p = HR[p + card5.code()];
	p = HR[p + card6.code()];
	return HR[p + card7.code()];
}