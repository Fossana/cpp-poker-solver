#include "TreeBuilder.h"
#include "TreeUtils.h"
#include "HandDistributionUtils.h"

//TEST(EquityCalculator, Calculate_UniformRangeVsUniformRangeOnFlop)
//{
//	FILE* inf = fopen("../HandRanks.dat", "rb");
//	assert(inf);
//	std::shared_ptr<HandEvaluator> handEvaluator = std::make_shared<HandEvaluator>(inf);
//	fclose(inf);
//	EquityCalculator equityCalculator(std::move(handEvaluator));
//
//	HandDistribution p1Range = GenerateUniformHandDistribution(CardSet());
//	HandDistribution p2Range = GenerateUniformHandDistribution(CardSet());
//	Board board(Card("Ac"), Card("Kc"), Card("Qc"));
//
//	EquityCalculatorResult res = equityCalculator.Calculate(p1Range, p2Range, board);
//
//	ASSERT_LE(fabs(res.p1Equity - 0.5), 1E-8);
//	ASSERT_LE(fabs(res.p2Equity - 0.5), 1E-8);
//}
//
//TEST(EquityCalculator, Calculate_UniformRangeVsUniformRangeOnTurn)
//{
//	FILE* inf = fopen("../HandRanks.dat", "rb");
//	assert(inf);
//	std::shared_ptr<HandEvaluator> handEvaluator = std::make_shared<HandEvaluator>(inf);
//	fclose(inf);
//	EquityCalculator equityCalculator(std::move(handEvaluator));
//
//	HandDistribution p1Range = GenerateUniformHandDistribution(CardSet());
//	HandDistribution p2Range = GenerateUniformHandDistribution(CardSet());
//	Board board(Card("Ac"), Card("Kc"), Card("Qc"), Card("Jc"));
//
//	EquityCalculatorResult res = equityCalculator.Calculate(p1Range, p2Range, board);
//
//	ASSERT_LE(fabs(res.p1Equity - 0.5), 1E-8);
//	ASSERT_LE(fabs(res.p2Equity - 0.5), 1E-8);
//}
//
//TEST(EquityCalculator, Calculate_UniformRangeVsUniformRangeOnRiver)
//{
//	FILE* inf = fopen("../HandRanks.dat", "rb");
//	assert(inf);
//	std::shared_ptr<HandEvaluator> handEvaluator = std::make_shared<HandEvaluator>(inf);
//	fclose(inf);
//	EquityCalculator equityCalculator(std::move(handEvaluator));
//
//	HandDistribution p1Range = GenerateUniformHandDistribution(CardSet());
//	HandDistribution p2Range = GenerateUniformHandDistribution(CardSet());
//	Board board(Card("Ac"), Card("Kc"), Card("Qc"), Card("Jc"), Card("Tc"));
//
//	EquityCalculatorResult res = equityCalculator.Calculate(p1Range, p2Range, board);
//
//	ASSERT_LE(fabs(res.p1Equity - 0.5), 1E-8);
//	ASSERT_LE(fabs(res.p2Equity - 0.5), 1E-8);
//}

void TestBuildingRiver()
{
	GameTree::TreeBuildSettings treeBuildSettings(
		GenerateUniformHandDistribution(CardSet()), // OOP preflop range
		GenerateUniformHandDistribution(CardSet()), // IP preflop range
		Street::RIVER,
		Board(Card("Kd"), Card("Jc"), Card("Ts"), Card("8s"), Card("Ts")),
		500, // initial pot
		1000, // starting stack
		GameTree::BetSettings({ 1.0 }, { 1.0 }, { 1.0 }, { 1.0 }, { 1.0 }, { 1.0 }), // OOP bet settings
		GameTree::BetSettings({ 1.0 }, { 1.0 }, { 1.0 }, { 1.0 }, { 1.0 }, { 1.0 }), // IP bet settings
		500, // minimum bet size
		0.67 // allin threshold
	);

	GameTree::TreeBuilder treeBuilder(treeBuildSettings);
	std::shared_ptr<GameTree::Node> tree = treeBuilder.Build();
	GameTree::Print(tree);
}

int main()
{
	TestBuildingRiver();
	return 0;
}