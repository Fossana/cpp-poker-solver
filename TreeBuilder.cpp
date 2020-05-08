#include "TreeBuilder.h"
#include "ActionUtils.h"
#include "BoardUtils.h"
#include "GameConstants.h"
#include <set>

namespace GameTree
{

TreeBuilder::TreeBuilder(const TreeBuildSettings& treeBuildSettings):
	treeBuildSettings(treeBuildSettings)
{
}

std::shared_ptr<ActionNode> TreeBuilder::Build()
{
	PlayerState ip(treeBuildSettings.startingStack(), PlayerId::IP);
	PlayerState oop(treeBuildSettings.startingStack(), PlayerId::OOP);
	GameState initialState(
		ip,
		oop,
		treeBuildSettings.initialStreet(),
		treeBuildSettings.initialPot(),
		treeBuildSettings.initialBoard(),
		treeBuildSettings.minimumBetSize()
	);

	std::shared_ptr<ActionNode> root = BuildActionNode(nullptr, initialState);
	return std::move(root);
}

std::shared_ptr<ActionNode> TreeBuilder::BuildActionNode(std::shared_ptr<Node> parent, const GameState& state)
{
	const PlayerState& activePlayer = state.GetActivePlayer();
	
	std::vector<Action> validActions = GenerateAllValidActionsForActivePlayer(state);
	std::shared_ptr<ActionNode> actionNode = std::make_shared<ActionNode>(std::move(parent), activePlayer.id(), state.street());

	for (Action action : validActions)
	{
		BuildActionNodeHelper(actionNode, state, action);
	}

	return actionNode;
}

std::vector<Action> TreeBuilder::GenerateAllValidActionsForActivePlayer(const GameState& state)
{
	std::vector<Action> possibleActions = GenerateAllPossibleActionsForActivePlayer(state);

	std::vector<Action> validActions;
	for (Action action : possibleActions)
	{
		if (IsActionValid(action, state))
		{
			validActions.push_back(action);
		}
	}

	return validActions;
}

std::vector<Action> TreeBuilder::GenerateAllPossibleActionsForActivePlayer(const GameState& state)
{
	std::vector<Action> possibleActions
	{
		Action(ActionType::FOLD),
		Action(ActionType::CHECK),
		Action(ActionType::CALL, state.GetActivePlayerCallAmount())
	};

	std::vector<Action> possibleBetActions = GenerateAllPossibleBetActionsForActivePlayer(state);
	std::vector<Action> possibleRaiseActions = GenerateAllPossibleRaiseActionsForActivePlayer(state);

	possibleActions.insert(possibleActions.end(), possibleBetActions.begin(), possibleBetActions.end());
	possibleActions.insert(possibleActions.end(), possibleRaiseActions.begin(), possibleRaiseActions.end());

	return possibleActions;
}

std::vector<Action> TreeBuilder::GenerateAllPossibleBetActionsForActivePlayer(const GameState& state)
{
	std::vector<Action> retval;

	const PlayerState& activePlayer = state.GetActivePlayer();
	const std::vector<double>& betSizes = GetBetSizes(state.street(), activePlayer.id());
	std::set<int> betAmounts;

	for (double betSize : betSizes)
	{
		int betAmount = (int) (betSize * state.pot());

		if (betAmount > activePlayer.stack())
		{
			betAmount = activePlayer.stack();
		}
		else if ((double) (betAmount / activePlayer.stack()) >= treeBuildSettings.allinThreshold())
		{
			betAmount = activePlayer.stack();
		}

		if (betAmount <= activePlayer.stack())
		{
			betAmounts.insert(betAmount);
		}
	}

	for (int betAmount : betAmounts)
	{
		retval.emplace_back(ActionType::BET, betAmount);
	}

	return retval;
}

std::vector<Action> TreeBuilder::GenerateAllPossibleRaiseActionsForActivePlayer(const GameState& state)
{
	std::vector<Action> retval;

	const PlayerState& activePlayer = state.GetActivePlayer();
	const std::vector<double>& raiseSizes = GetRaiseSizes(state.street(), activePlayer.id());
	std::set<int> raiseAmounts;
	int stackAtStartOfRound = activePlayer.stack() + activePlayer.chipsCommitted();

	for (double raiseSize : raiseSizes)
	{
		int totalChipsCommittedAfterRaise =	(int) (
												activePlayer.chipsCommitted() +
												state.GetActivePlayerCallAmount() +
												raiseSize * (state.pot() + state.GetActivePlayerCallAmount())
											);

		if (totalChipsCommittedAfterRaise > stackAtStartOfRound)
		{
			totalChipsCommittedAfterRaise = stackAtStartOfRound;
		}
		else if ((double) (totalChipsCommittedAfterRaise / stackAtStartOfRound) >= treeBuildSettings.allinThreshold())
		{
			totalChipsCommittedAfterRaise = stackAtStartOfRound;
		}

		if (totalChipsCommittedAfterRaise <= stackAtStartOfRound)
		{
			raiseAmounts.insert(totalChipsCommittedAfterRaise);
		}
	}

	for (int raiseAmount : raiseAmounts)
	{
		retval.emplace_back(ActionType::RAISE, raiseAmount);
	}

	return retval;
}

bool TreeBuilder::TerminalNodeIsNext(const GameState& state)
{
	return	state.BothPlayersAreAllin() ||
			state.EitherPlayerHasFolded() ||
			state.street() == Street::RIVER;
}

void TreeBuilder::BuildActionNodeHelper(std::shared_ptr<ActionNode>& actionNode, const GameState& state, const Action& action)
{
	GameState nextState(state);
	nextState.ApplyAction(action);

	if (nextState.currentRoundHasCompleted())
	{
		if (TerminalNodeIsNext(nextState))
		{
			std::shared_ptr<TerminalNode> child = BuildTerminalNode(actionNode, nextState);
			actionNode->AddChild(action, std::move(child));
		}
		else
		{
			std::shared_ptr<ChanceNode> child = BuildChanceNode(actionNode, nextState);
			actionNode->AddChild(action, std::move(child));
		}
	}
	else
	{
		std::shared_ptr<ActionNode> child = BuildActionNode(actionNode, nextState);
		actionNode->AddChild(action, std::move(child));
	}
}

std::shared_ptr<ChanceNode> TreeBuilder::BuildChanceNode(std::shared_ptr<Node> parent, const GameState& state)
{
	std::shared_ptr<ChanceNode> chanceNode(nullptr);

	if (state.street() == Street::FLOP)
	{
		chanceNode = std::make_shared<ChanceNode>(std::move(parent), ChanceNodeType::DEAL_TURN);
	}
	else if (state.street() == Street::TURN)
	{
		chanceNode = std::make_shared<ChanceNode>(std::move(parent), ChanceNodeType::DEAL_RIVER);
	}

	GameState nextState = GameState(state);
	nextState.TransitionToNextStreet();

	std::shared_ptr<Node> actionNode = BuildActionNode(chanceNode, nextState);
	chanceNode->SetChild(move(actionNode));

	return std::move(chanceNode);
}

std::shared_ptr<TerminalNode> TreeBuilder::BuildTerminalNode(std::shared_ptr<Node> parent, const GameState& state)
{
	std::shared_ptr<TerminalNode> terminalNode(nullptr);

	std::reference_wrapper<const std::shared_ptr<Node>> temp = parent;
	while (temp.get()->type() != NodeType::ACTION)
	{
		temp = temp.get()->parent();
	}
	PlayerId lastToAct = std::static_pointer_cast<ActionNode>(temp.get())->owner();

	if (state.BothPlayersAreAllin() && state.street() != Street::RIVER)
	{
		terminalNode = std::make_shared<TerminalNode>(move(parent), TerminalNodeType::ALLIN_BEFORE_RIVER, state.pot(), lastToAct);
	}
	else if (state.EitherPlayerHasFolded())
	{
		terminalNode = std::make_shared<TerminalNode>(move(parent), TerminalNodeType::NON_SHOWDOWN, state.pot(), lastToAct);
	}
	else // showdown
	{
		terminalNode = std::make_shared<TerminalNode>(move(parent), TerminalNodeType::SHOWDOWN, state.pot(), lastToAct);
	}

	return std::move(terminalNode);
}

const std::vector<double>& TreeBuilder::GetBetSizes(const Street street, const PlayerId id)
{
	switch (street)
	{
	case Street::RIVER:
		return id == PlayerId::OOP ? treeBuildSettings.oopBetSettings().riverBetSizes() : treeBuildSettings.ipBetSettings().riverBetSizes();
	case Street::TURN:
		return id == PlayerId::OOP ? treeBuildSettings.oopBetSettings().turnBetSizes() : treeBuildSettings.ipBetSettings().turnBetSizes();
	case Street::FLOP:
		return id == PlayerId::OOP ? treeBuildSettings.oopBetSettings().flopBetSizes() : treeBuildSettings.ipBetSettings().flopBetSizes();
	}
}

const std::vector<double>& TreeBuilder::GetRaiseSizes(const Street street, const PlayerId id)
{
	switch (street)
	{
	case Street::RIVER:
		return id == PlayerId::OOP ? treeBuildSettings.oopBetSettings().riverRaiseSizes() : treeBuildSettings.ipBetSettings().riverRaiseSizes();
	case Street::TURN:
		return id == PlayerId::OOP ? treeBuildSettings.oopBetSettings().turnRaiseSizes() : treeBuildSettings.ipBetSettings().turnRaiseSizes();
	case Street::FLOP:
		return id == PlayerId::OOP ? treeBuildSettings.oopBetSettings().flopRaiseSizes() : treeBuildSettings.ipBetSettings().flopRaiseSizes();
	}
}

} // GameTree