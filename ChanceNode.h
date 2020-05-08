#ifndef GAME_TREE_CHANCE_NODE_H_
#define GAME_TREE_CHANCE_NODE_H_

#include "Node.h"
#include "ChanceNodeTypeEnum.h"

namespace GameTree
{

class ChanceNode : public Node
{
public:
	ChanceNode(std::shared_ptr<Node> parent, const ChanceNodeType type);
	~ChanceNode();

	inline const std::shared_ptr<Node>& child() const
	{
		return child_;
	}

	inline std::shared_ptr<Node>& child()
	{
		return child_;
	}

	inline ChanceNodeType type() const
	{
		return type_;
	}

	void SetChild(std::shared_ptr<Node> child);

private:
	ChanceNodeType type_;
	std::shared_ptr<Node> child_;
};

} // GameTree

#endif // GAME_TREE_CHANCE_NODE_H_