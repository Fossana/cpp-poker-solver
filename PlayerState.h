#ifndef GAME_TREE_PLAYER_STATE_H_
#define GAME_TREE_PLAYER_STATE_H_

#include "PlayerIdEnum.h"

namespace GameTree
{

class PlayerState
{
public:
	PlayerState(const int numChipsInStack, const PlayerId id);
	PlayerState(const PlayerState& other);

	inline PlayerId id() const
	{
		return id_;
	}

	inline int stack() const
	{
		return stack_;
	}

	inline int chipsCommitted() const
	{
		return chipsCommitted_;
	}

	inline bool hasFolded() const
	{
		return hasFolded_;
	}

	void Set_chipsCommitted(const int value);
	void Fold();
	void CommitChips(const int amount);
	bool IsAllin() const;

private:
	PlayerId id_;
	int stack_;
	int chipsCommitted_;
	bool hasFolded_;
};

} // GameTree

#endif // GAME_TREE_PLAYER_STATE_H_
