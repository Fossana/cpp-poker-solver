#ifndef HAND_EVALUATOR_H_
#define HAND_EVALUATOR_H_

#include "Card.h"
#include <cstdio>

class HandEvaluator
{
public:
	HandEvaluator(FILE* lookupTable);

	int Evaluate_SevenCards(
		const Card& card1,
		const Card& card2,
		const Card& card3,
		const Card& card4,
		const Card& card5,
		const Card& card6,
		const Card& card7
	);

private:
	int HR[32487834];
};

#endif // HAND_EVALUATOR_H_