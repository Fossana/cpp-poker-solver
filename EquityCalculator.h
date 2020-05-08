#ifndef EQUITY_CALCULATOR_H_
#define EQUITY_CALCULATOR_H_

#include "HandEvaluator.h"
#include "HandDistribution.h"
#include "Board.h"
#include "CardSet.h"
#include <memory>

struct EquityCalculatorResult
{
	EquityCalculatorResult():
		p1Equity(0.0),
		p2Equity(0.0)
	{
	}

	double p1Equity;
	double p2Equity;
};

class EquityCalculator
{
public:
	EquityCalculator(std::shared_ptr<HandEvaluator> handEvaluator);
	EquityCalculatorResult Calculate(const HandDistribution& p1Range, const HandDistribution& p2Range, const Board& board);

private:
	void EnumerateShowdowns(
		const Hand& p1Hand,
		const Hand& p2Hand,
		CardSet& deadCards,
		const Board& board,
		double& p1Equity,
		double& p2Equity,
		int& numTrials
	);

	void EnumerateShowdownsFromFlopBoard(
		const Hand& p1Hand,
		const Hand& p2Hand,
		CardSet& deadCards,
		const Board& flopBoard,
		double& p1Equity,
		double& p2Equity,
		int& numTrials
	);

	void EnumerateShowdownsFromTurnBoard(
		const Hand& p1Hand,
		const Hand& p2Hand,
		CardSet& deadCards,
		const Board& turnBoard,
		double& p1Equity,
		double& p2Equity,
		int& numTrials
	);

	void EvaluateShowdown(
		const Hand& p1Hand,
		const Hand& p2Hand,
		const Board& riverBoard,
		double& p1Equity,
		double& p2Equity,
		int& numTrials
	);

	std::shared_ptr<HandEvaluator> handEvaluator;
};

#endif // EQUITY_CALCULATOR_H_