#include "Action.h"

Action::Action(const ActionType type, const int amount):
	type_(type),
	amount_(amount)
{
}

bool Action::operator()(const Action& lhs, const Action& rhs) const {
	if (lhs.type() == rhs.type())
	{
		return lhs.amount() < rhs.amount();
	}

	return lhs.type() < rhs.type();
}

bool Action::operator<(const Action& other) const
{
	return operator()(*this, other);
}

bool Action::operator==(const Action& other) const
{
	return	type_ == other.type_ &&
			amount_ == other.amount_;
}