#include "TreeUtils.h"
#include "ActionNode.h"
#include "ChanceNode.h"
#include "TerminalNode.h"
#include <string>
#include <iostream>
#include <regex>

namespace GameTree
{

namespace
{

std::string GetString(const std::shared_ptr<Node>& node);

std::string GetString(const Action action, const std::shared_ptr<Node>& child, const PlayerId owner)
{
	std::string retVal = owner == PlayerId::OOP ? "OOP" : "IP";

	switch (action.type())
	{
	case ActionType::FOLD:
		retVal += ": FOLD\n";
		break;
	case ActionType::CHECK:
		retVal += ": CHECK\n";
		break;
	case ActionType::CALL:
		retVal += ": CALL " + std::to_string(action.amount()) + '\n';;
		break;
	case ActionType::BET:
		retVal += ": BET " + std::to_string(action.amount()) + '\n';;
		break;
	case ActionType::RAISE:
		retVal += ": RAISE " + std::to_string(action.amount()) + '\n';
		break;
	}

	std::string append = GetString(child);
	retVal += "    " + std::regex_replace(append, std::regex("\n"), "\n    ");

	return retVal;
}

std::string GetString(const std::shared_ptr<ActionNode>& actionNode)
{
	std::string retVal = "";

	for (auto it = actionNode->begin(); it != actionNode->end(); ++it)
	{
		std::string append = GetString(it->first, it->second, actionNode->owner());
		if (it != std::prev(actionNode->end(), 1))
		{
			retVal += append + '\n';
		}
	}

	return retVal;
}

std::string GetString(const std::shared_ptr<ChanceNode>& chanceNode)
{
	std::string retVal = "";

	if (chanceNode->type() == ChanceNodeType::DEAL_TURN)
	{
		retVal = "DEAL_TURN\n";
	}
	else if (chanceNode->type() == ChanceNodeType::DEAL_RIVER)
	{
		retVal = "DEAL_RIVER\n";
	}

	std::string append = GetString(chanceNode->child());
	retVal += "    " + std::regex_replace(append, std::regex("\n"), "\n    ");

	return retVal;
}

std::string GetString(const std::shared_ptr<TerminalNode>& terminalNode)
{
	std::string retval;

	switch (terminalNode->type())
	{
	case TerminalNodeType::SHOWDOWN:
		retval += "SHOWDOWN: ";
		break;
	case TerminalNodeType::NON_SHOWDOWN:
		retval += "UNCONTESTED: ";
		break;
	case TerminalNodeType::ALLIN_BEFORE_RIVER:
		retval += "ALLIN: ";
		break;
	}

	retval += std::to_string(terminalNode->pot()) +
		" LAST_TO_ACT: " +
		(terminalNode->lastToAct() == PlayerId::OOP ? "OOP" : "IP");

	return retval;
}

std::string GetString(const std::shared_ptr<Node>& node)
{
	std::string retval = "";

	switch (node->type())
	{
	case NodeType::TERMINAL:
		retval = GetString(std::static_pointer_cast<TerminalNode>(node));
		break;
	case NodeType::ACTION:
		retval = GetString(std::static_pointer_cast<ActionNode>(node));
		break;
	case NodeType::CHANCE:
		retval = GetString(std::static_pointer_cast<ChanceNode>(node));
		break;
	}

	return retval;
}

} // anonymous

void Print(const std::shared_ptr<Node>& root)
{
	std::cout << GetString(root);
}

} // GameTree