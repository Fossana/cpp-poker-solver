#include "TreeBuilder.h"
#include "TreeUtils.h"
#include "HandDistributionUtils.h"

void TestRiver()
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
		0.67f // allin threshold
	);

	GameTree::TreeBuilder treeBuilder(treeBuildSettings);
	std::shared_ptr<GameTree::Node> tree = treeBuilder.Build();
	GameTree::Print(tree);
}

int main()
{
	TestRiver();
	return 0;
}