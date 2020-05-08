#ifndef ACTION_H_
#define ACTION_H_

#include "ActionTypeEnum.h"
#include "HashUtils.h"

class Action
{
public:
	Action(const ActionType type, const int amount = 0);

	inline ActionType type() const
	{
		return type_;
	}

	inline int amount() const
	{
		return amount_;
	}

	bool operator()(const Action& lhs, const Action& rhs) const;
	bool operator<(const Action& other) const;
	bool operator==(const Action& other) const;

private:
	ActionType type_;
	int amount_;
};

MAKE_HASHABLE(Action, t.type(), t.amount())

#endif // ACTION_H_