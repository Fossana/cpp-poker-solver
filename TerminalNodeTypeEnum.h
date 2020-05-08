#ifndef GAME_TREE_TERMINAL_NODE_TYPE_ENUM_H_
#define GAME_TREE_TERMINAL_NODE_TYPE_ENUM_H_

namespace GameTree
{

enum TerminalNodeType
{
	NON_SHOWDOWN = 0,
	SHOWDOWN,
	ALLIN_BEFORE_RIVER
};

} // GameTree

#endif // GAME_TREE_TERMINAL_NODE_TYPE_ENUM_H_