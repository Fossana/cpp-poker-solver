#include "EquityCalculator.h"

EquityCalculator::EquityCalculator(std::shared_ptr<HandEvaluator> handEvaluator):
	handEvaluator(std::move(handEvaluator))
{
}

EquityCalculatorResult EquityCalculator::Calculate(const HandDistribution& p1Range, const HandDistribution& p2Range, const Board& board)
{
	EquityCalculatorResult retval;

	CardSet deadCards;

	for (Card card : board)
	{
		deadCards.Insert(card);
	}

	int numTrials = 0;

	for (const Hand& p1Hand : p1Range)
	{
		if (deadCards.Contains(p1Hand.card1()) || deadCards.Contains(p1Hand.card2()))
		{
			continue;
		}

		deadCards.Insert(p1Hand.card1());
		deadCards.Insert(p1Hand.card2());

		for (const Hand& p2Hand : p2Range)
		{
			if (deadCards.Contains(p2Hand.card1()) || deadCards.Contains(p2Hand.card2()))
			{
				continue;
			}

			deadCards.Insert(p2Hand.card1());
			deadCards.Insert(p2Hand.card2());

			EnumerateShowdowns(p1Hand, p2Hand, deadCards, board, retval.p1Equity, retval.p2Equity, numTrials);

			deadCards.Remove(p2Hand.card1());
			deadCards.Remove(p2Hand.card2());
		}

		deadCards.Remove(p1Hand.card1());
		deadCards.Remove(p1Hand.card2());
	}

	retval.p1Equity /= numTrials;
	retval.p2Equity /= numTrials;

	return retval;
}

void EquityCalculator::EnumerateShowdowns(
	const Hand& p1Hand,
	const Hand& p2Hand,
	CardSet& deadCards,
	const Board& board,
	double& p1Equity,
	double& p2Equity,
	int& numTrials
)
{
	switch (board.size())
	{
		case 5:
			EvaluateShowdown(p1Hand, p2Hand, board, p1Equity, p2Equity, numTrials);
			break;
		case 4:
			EnumerateShowdownsFromTurnBoard(p1Hand, p2Hand, deadCards, board, p1Equity, p2Equity, numTrials);
			break;
		case 3:
			EnumerateShowdownsFromFlopBoard(p1Hand, p2Hand, deadCards, board, p1Equity, p2Equity, numTrials);
			break;
	}
}

void EquityCalculator::EnumerateShowdownsFromFlopBoard(
	const Hand& p1Hand,
	const Hand& p2Hand,
	CardSet& deadCards,
	const Board& flopBoard,
	double& p1Equity,
	double& p2Equity,
	int& numTrials
)
{
	for (uint8_t encodedFourthCard = Card::ENCODED_CARD_FIRST; encodedFourthCard <= Card::ENCODED_CARD_LAST; ++encodedFourthCard)
	{
		Card turn(encodedFourthCard);
		if (deadCards.Contains(turn))
		{
			continue;
		}

		deadCards.Insert(turn);

		Board turnBoard(flopBoard);
		turnBoard.Add(turn);

		for (uint8_t encodedFifthCard = encodedFourthCard + 1; encodedFifthCard <= Card::ENCODED_CARD_LAST; ++encodedFifthCard)
		{
			Card river(encodedFifthCard);
			if (deadCards.Contains(river))
			{
				continue;
			}

			Board riverBoard(turnBoard);
			riverBoard.Add(river);
			EvaluateShowdown(p1Hand, p2Hand, riverBoard, p1Equity, p2Equity, numTrials);
		}

		deadCards.Remove(turn);
	}
}

void EquityCalculator::EnumerateShowdownsFromTurnBoard(
	const Hand& p1Hand,
	const Hand& p2Hand,
	CardSet& deadCards,
	const Board& turnBoard,
	double& p1Equity,
	double& p2Equity,
	int& numTrials
)
{
	for (uint8_t encodedFifthCard = Card::ENCODED_CARD_FIRST; encodedFifthCard <= Card::ENCODED_CARD_LAST; ++encodedFifthCard)
	{
		Card river(encodedFifthCard);
		if (deadCards.Contains(river))
		{
			continue;
		}

		Board riverBoard(turnBoard);
		riverBoard.Add(river);
		EvaluateShowdown(p1Hand, p2Hand, riverBoard, p1Equity, p2Equity, numTrials);
	}
}

void EquityCalculator::EvaluateShowdown(
	const Hand& p1Hand,
	const Hand& p2Hand,
	const Board& board,
	double& p1Equity,
	double& p2Equity,
	int& numTrials
)
{
	int p1HandStrength = handEvaluator->Evaluate_SevenCards(
		p1Hand.card1(),
		p1Hand.card2(),
		board[0],
		board[1],
		board[2],
		board[3],
		board[4]
	);

	int p2HandStrength = handEvaluator->Evaluate_SevenCards(
		p2Hand.card1(),
		p2Hand.card2(),
		board[0],
		board[1],
		board[2],
		board[3],
		board[4]
	);

	if (p1HandStrength > p2HandStrength)
	{
		p1Equity += 1.0;
	}
	else if (p1HandStrength < p2HandStrength)
	{
		p2Equity += 1.0;
	}
	else
	{
		p1Equity += 0.5;
		p2Equity += 0.5;
	}

	++numTrials;
}