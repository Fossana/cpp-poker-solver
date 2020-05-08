#include "PlayerState.h"

namespace GameTree
{

PlayerState::PlayerState(const int numChipsInStack, const PlayerId id):
	stack_(numChipsInStack),
	id_(id),
	chipsCommitted_(0),
	hasFolded_(false)
{
}

PlayerState::PlayerState(const PlayerState& other):
	stack_(other.stack_),
	id_(other.id_),
	chipsCommitted_(other.chipsCommitted_),
	hasFolded_(other.hasFolded_)
{
}

void PlayerState::Set_chipsCommitted(const int value)
{
	chipsCommitted_ = value;
}

void PlayerState::Fold()
{
	hasFolded_ = true;
}

void PlayerState::CommitChips(const int amount)
{
	chipsCommitted_ += amount;
	stack_ -= amount;
}

bool PlayerState::IsAllin() const
{
	return stack_ == 0;
}

} // GameTree