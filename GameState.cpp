#include "GameState.h"
#include <algorithm>

namespace GameTree
{

GameState::GameState(
	const PlayerState& ip,
	const PlayerState& oop,
	const Street street,
	const int pot,
	const Board& board,
	const int minimumBetSize
):
	ipPlayer(ip),
	oopPlayer(oop),
	street_(street),
	pot_(pot),
	board(board),
	currentRoundHasCompleted_(false),
	minimumBetSize_(minimumBetSize),
	minimumRaiseSize_(0)
{
	activePlayer = &this->oopPlayer;
	lastToActPlayer = &this->ipPlayer;
}

GameState::GameState(const GameState& other):
	ipPlayer(other.ipPlayer),
	oopPlayer(other.oopPlayer),
	street_(other.street_),
	pot_(other.pot_),
	board(other.board),
	currentRoundHasCompleted_(other.currentRoundHasCompleted_),
	minimumBetSize_(other.minimumBetSize_),
	minimumRaiseSize_(other.minimumRaiseSize_)
{
	activePlayer = (other.activePlayer->id() == PlayerId::OOP) ? &this->oopPlayer : &this->ipPlayer;
	lastToActPlayer = (other.lastToActPlayer->id() == PlayerId::OOP) ? &this->oopPlayer : &this->ipPlayer;
}

int GameState::GetActivePlayerCallAmount() const
{
	return GetHighestAmountOfChipsCommitted() - activePlayer->chipsCommitted();
}

const PlayerState& GameState::GetActivePlayer() const
{
	return *activePlayer;
}

void GameState::ApplyAction(const Action& action)
{
	switch (action.type())
	{
		case ActionType::FOLD:
			ApplyAction_Fold();
			break;
		case ActionType::CHECK:
			ApplyAction_Check();
			break;
		case ActionType::CALL:
			ApplyAction_Call(action);
			break;
		case ActionType::BET:
			ApplyAction_Bet(action);
			break;
		case ActionType::RAISE:
			ApplyAction_Raise(action);
			break;
	}

	SwitchActivePlayer();
}

void GameState::ApplyAction_Fold()
{
	activePlayer->Fold();
	pot_ -= GetActivePlayerCallAmount();
	currentRoundHasCompleted_ = true;
}

void GameState::ApplyAction_Check()
{
	if (activePlayer == lastToActPlayer)
	{
		currentRoundHasCompleted_ = true;
	}
}

void GameState::ApplyAction_Call(const Action& action)
{
	currentRoundHasCompleted_ = true;
	activePlayer->CommitChips(action.amount());
	pot_ += action.amount();
}

void GameState::ApplyAction_Bet(const Action& action)
{
	activePlayer->CommitChips(action.amount());
	pot_ += action.amount();
	minimumRaiseSize_ = action.amount();
	SwitchLastToActPlayer();
}

void GameState::ApplyAction_Raise(const Action& action)
{
	int numChipsToCommit = action.amount() - activePlayer->chipsCommitted();
	activePlayer->CommitChips(numChipsToCommit);
	pot_ += numChipsToCommit;
	int raiseSize = action.amount() - GetHighestAmountOfChipsCommitted();
	if (raiseSize > minimumRaiseSize_)
	{
		minimumRaiseSize_ = raiseSize;
	}
	SwitchLastToActPlayer();
}

bool GameState::BetHasBeenMadeDuringCurrentRound() const
{
	return ipPlayer.chipsCommitted() > 0 || oopPlayer.chipsCommitted() > 0;
}

int GameState::GetHighestAmountOfChipsCommitted() const
{
	return std::max(ipPlayer.chipsCommitted(), oopPlayer.chipsCommitted());
}

void GameState::SwitchLastToActPlayer()
{
	lastToActPlayer = (lastToActPlayer == &ipPlayer) ? &oopPlayer : &ipPlayer;
}

void GameState::SwitchActivePlayer()
{
	activePlayer = (activePlayer == &ipPlayer) ? &oopPlayer : &ipPlayer;
}

bool GameState::BothPlayersAreAllin() const
{
	return ipPlayer.IsAllin() && oopPlayer.IsAllin();
}

bool GameState::EitherPlayerHasFolded() const
{
	return ipPlayer.hasFolded() || oopPlayer.hasFolded();
}

void GameState::TransitionToNextStreet()
{
	if (street_ == Street::FLOP)
	{
		street_ = Street::TURN;
	}
	else if (street_ == Street::TURN)
	{
		street_ = Street::RIVER;
	}

	currentRoundHasCompleted_ = false;

	ipPlayer.Set_chipsCommitted(0);
	oopPlayer.Set_chipsCommitted(0);

	activePlayer = &oopPlayer;
	lastToActPlayer = &ipPlayer;
}

} // GameTree