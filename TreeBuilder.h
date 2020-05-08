#ifndef GAME_TREE_TREE_BUILDER_H_
#define GAME_TREE_TREE_BUILDER_H_

#include "TreeBuildSettings.h"
#include "ActionNode.h"
#include "ChanceNode.h"
#include "TerminalNode.h"
#include "GameState.h"

namespace GameTree
{

class TreeBuilder
{
public:
	TreeBuilder(const TreeBuildSettings& treeBuildSettings);
	std::shared_ptr<ActionNode> Build();

private:
	std::shared_ptr<ActionNode> BuildActionNode(std::shared_ptr<Node> parent, const GameState& state);
	void BuildActionNodeHelper(std::shared_ptr<ActionNode>& actionNode, const GameState& state, const Action& action);
	std::shared_ptr<ChanceNode> BuildChanceNode(std::shared_ptr<Node> parent, const GameState& state);
	std::shared_ptr<TerminalNode> BuildTerminalNode(std::shared_ptr<Node> parent, const GameState& state);
	std::vector<Action> GenerateAllValidActionsForActivePlayer(const GameState& state);
	std::vector<Action> GenerateAllPossibleActionsForActivePlayer(const GameState& state);
	std::vector<Action> GenerateAllPossibleBetActionsForActivePlayer(const GameState& state);
	std::vector<Action> GenerateAllPossibleRaiseActionsForActivePlayer(const GameState& state);
	const std::vector<double>& GetBetSizes(const Street street, const PlayerId id);
	const std::vector<double>& GetRaiseSizes(const Street street, const PlayerId id);

	TreeBuildSettings treeBuildSettings;
};

} // GameTree

#endif // GAME_TREE_TREE_BUILDER_H_