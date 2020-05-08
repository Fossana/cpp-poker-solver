#ifndef GAME_TREE_ACTION_NODE_H_
#define GAME_TREE_ACTION_NODE_H_

#include "Node.h"
#include "PlayerIdEnum.h"
#include "Action.h"
#include "Board.h"
#include <utility>
#include <map>

namespace GameTree
{

class ActionNode : public Node
{
public:
	typedef std::map<Action, std::shared_ptr<Node>> ActionChildMap;
	ActionNode(std::shared_ptr<Node> parent, const PlayerId owner, const Street street);

	ActionChildMap::const_iterator begin() const;
	ActionChildMap::const_iterator end() const;
	ActionChildMap::iterator begin();
	ActionChildMap::iterator end();

	inline PlayerId owner() const
	{
		return owner_;
	}

	inline Street street() const
	{
		return street_;
	}

	int GetNumActions() const;
	void AddChild(const Action action, std::shared_ptr<Node> child);

protected:
	ActionChildMap actionToChild_;
	PlayerId owner_;
	Street street_;
};

} // GameTree

#endif // GAME_TREE_ACTION_NODE_H_