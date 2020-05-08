#ifndef GAME_TREE_TERMINAL_NODE_H_
#define GAME_TREE_TERMINAL_NODE_H_

#include "TerminalNodeTypeEnum.h"
#include "Node.h"
#include "PlayerIdEnum.h"

namespace GameTree
{

class TerminalNode : public Node
{
public:
	TerminalNode(std::shared_ptr<Node> parent, const TerminalNodeType type, const int pot, const PlayerId lastToAct);
	~TerminalNode();

	inline PlayerId lastToAct() const
	{
		return lastToAct_;
	}

	inline TerminalNodeType type() const
	{
		return type_;
	}

	inline int pot() const
	{
		return pot_;
	}

private:
	TerminalNodeType type_;
	int pot_;
	PlayerId lastToAct_;
};

} // GameTree

#endif // GAME_TREE_TERMINAL_NODE_H_