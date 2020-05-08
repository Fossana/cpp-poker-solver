#ifndef GAME_TREE_GAME_STATE_H_
#define GAME_TREE_GAME_STATE_H_

#include "PlayerState.h"
#include "Action.h"
#include "Board.h"

namespace GameTree
{

class GameState
{
public:
	GameState(
		const PlayerState& ip,
		const PlayerState& oop,
		const Street street,
		const int pot,
		const Board& board,
		const int minimumBetSize
	);
	GameState(const GameState& other);

	inline int minimumBetSize() const
	{
		return minimumBetSize_;
	}

	inline int minimumRaiseSize() const
	{
		return minimumRaiseSize_;
	}

	inline Street street() const
	{
		return street_;
	}

	inline int pot() const
	{
		return pot_;
	}

	inline bool currentRoundHasCompleted() const
	{
		return currentRoundHasCompleted_;
	}

	int GetActivePlayerCallAmount() const;
	const PlayerState& GetActivePlayer() const;
	void ApplyAction(const Action& action);
	bool BothPlayersAreAllin() const;
	bool EitherPlayerHasFolded() const;
	bool BetHasBeenMadeDuringCurrentRound() const;
	void TransitionToNextStreet();

private:
	void SwitchActivePlayer();
	void SwitchLastToActPlayer();
	int GetHighestAmountOfChipsCommitted() const;
	void ApplyAction_Fold();
	void ApplyAction_Check();
	void ApplyAction_Call(const Action& action);
	void ApplyAction_Bet(const Action& action);
	void ApplyAction_Raise(const Action& action);

	PlayerState ipPlayer;
	PlayerState oopPlayer;

	PlayerState* activePlayer;
	PlayerState* lastToActPlayer;

	Street street_;
	int pot_;
	Board board;

	bool currentRoundHasCompleted_;

	int minimumBetSize_;
	int minimumRaiseSize_;
};

} // GameTree

#endif // GAME_TREE_GAME_STATE_H_