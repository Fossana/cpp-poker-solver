#ifndef ACTION_UTILS_H_
#define ACTION_UTILS_H_

#include "Action.h"
#include "GameState.h"

bool IsActionValid(const Action& action, const GameTree::GameState& state);

#endif // ACTION_UTILS_H_