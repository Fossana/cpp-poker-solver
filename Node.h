#ifndef GAME_TREE_NODE_H_
#define GAME_TREE_NODE_H_

#include "NodeTypeEnum.h"
#include <memory>

namespace GameTree
{

class Node
{
public:
	Node(std::shared_ptr<Node> parent, const NodeType type);
	virtual ~Node() = 0;

	inline const std::shared_ptr<Node>& parent() const
	{
		return parent_;
	}

	inline NodeType type() const
	{
		return type_;
	}

private:
	std::shared_ptr<Node> parent_;
	NodeType type_;
};

} // GameTree

#endif // GAME_TREE_NODE_H_