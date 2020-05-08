#include "TerminalNode.h"

namespace GameTree
{

TerminalNode::TerminalNode(std::shared_ptr<Node> parent, const TerminalNodeType type, const int pot, const PlayerId lastToAct):
	Node(std::move(parent), NodeType::TERMINAL),
	type_(type),
	pot_(pot),
	lastToAct_(lastToAct)
{
}

TerminalNode::~TerminalNode() = default;

} // GameTree