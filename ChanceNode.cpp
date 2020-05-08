#include "ChanceNode.h"

namespace GameTree
{

ChanceNode::ChanceNode(std::shared_ptr<Node> parent, const ChanceNodeType type):
	Node(move(parent), NodeType::CHANCE),
	type_(type)
{
}

ChanceNode::~ChanceNode() = default;

void ChanceNode::SetChild(std::shared_ptr<Node> child)
{
	child_ = std::move(child);
}

} // GameTree