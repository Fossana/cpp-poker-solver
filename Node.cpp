#include "Node.h"

namespace GameTree
{

Node::Node(std::shared_ptr<Node> parent, const NodeType type):
	parent_(move(parent)),
	type_(type)
{
}

Node::~Node() = default;

} // GameTree