#include "ActionUtils.h"

namespace
{

bool IsActionValid_Fold(const Action& foldAction, const GameTree::GameState& state)
{
	return foldAction.amount() == 0 && state.BetHasBeenMadeDuringCurrentRound();
}

bool IsActionValid_Check(const Action& checkAction, const GameTree::GameState& state)
{
	return checkAction.amount() == 0 && !state.BetHasBeenMadeDuringCurrentRound();
}

bool IsActionValid_Call(const Action& callAction, const GameTree::GameState& state)
{
	const GameTree::PlayerState& activePlayer = state.GetActivePlayer();
	int callAmount = state.GetActivePlayerCallAmount();

	return	callAmount > 0 && (
				callAction.amount() == callAmount &&
				callAction.amount() <= activePlayer.stack() ||
				callAction.amount() == activePlayer.stack()
			);
}

bool IsActionValid_Bet(const Action& betAction, const GameTree::GameState& state)
{
	const GameTree::PlayerState& activePlayer = state.GetActivePlayer();

	return	!state.BetHasBeenMadeDuringCurrentRound() &&
			betAction.amount() > 0 && (
				betAction.amount() >= state.minimumBetSize() &&
				betAction.amount() <= activePlayer.stack() ||
				betAction.amount() == activePlayer.stack()
			);
}

bool IsActionValid_Raise(const Action& raiseAction, const GameTree::GameState& state)
{
	const GameTree::PlayerState& activePlayer = state.GetActivePlayer();

	int numChipsPotentiallyBeingCommitted = raiseAction.amount() - activePlayer.chipsCommitted();
	int raiseSize = numChipsPotentiallyBeingCommitted - state.GetActivePlayerCallAmount();

	return	state.GetActivePlayerCallAmount() > 0 &&
			raiseSize > 0 && (
				raiseSize >= state.minimumRaiseSize() &&
				numChipsPotentiallyBeingCommitted <= activePlayer.stack() ||
				numChipsPotentiallyBeingCommitted == activePlayer.stack()
			);
}

} // anonymous

bool IsActionValid(const Action& action, const GameTree::GameState& state)
{
	bool retval = false;

	switch (action.type())
	{
	case ActionType::FOLD:
		retval = IsActionValid_Fold(action, state);
		break;
	case ActionType::CHECK:
		retval = IsActionValid_Check(action, state);
		break;
	case ActionType::CALL:
		retval = IsActionValid_Call(action, state);
		break;
	case ActionType::BET:
		retval = IsActionValid_Bet(action, state);
		break;
	case ActionType::RAISE:
		retval = IsActionValid_Raise(action, state);
		break;
	}

	return retval;
}