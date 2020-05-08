#include "ActionNode.h"

namespace GameTree
{

ActionNode::ActionNode(
	std::shared_ptr<Node> parent,
	const PlayerId owner,
	const Street street
):
	Node(move(parent), NodeType::ACTION),
	owner_(owner),
	street_(street)
{
}

ActionNode::ActionChildMap::const_iterator ActionNode::begin() const
{
	return actionToChild_.begin();
}

ActionNode::ActionChildMap::const_iterator ActionNode::end() const
{
	return actionToChild_.end();
}

ActionNode::ActionChildMap::iterator ActionNode::begin()
{
	return actionToChild_.begin();
}

ActionNode::ActionChildMap::iterator ActionNode::end()
{
	return actionToChild_.end();
}

void ActionNode::AddChild(const Action action, std::shared_ptr<Node> child)
{
	actionToChild_.emplace(action, std::move(child));
}

int ActionNode::GetNumActions() const
{
	return static_cast<int>(actionToChild_.size());
}

} // GameTree