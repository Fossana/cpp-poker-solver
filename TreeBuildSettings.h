#ifndef GAME_TREE_TREE_BUILD_SETTINGS_H
#define GAME_TREE_TREE_BUILD_SETTINGS_H

#include "BetSettings.h"
#include "HandDistribution.h"
#include "Board.h"

namespace GameTree
{

class TreeBuildSettings
{
public:
	TreeBuildSettings(
		const HandDistribution& ipPreflopRange,
		const HandDistribution& oopPreflopRange,
		const Street initialStreet,
		const Board& initialBoard,
		const int initialPot,
		const int startingStack,
		const BetSettings& ipBetSettings,
		const BetSettings& oopBetSettings,
		const int minimumBetSize,
		const double allinThreshold
	);
	TreeBuildSettings(const TreeBuildSettings& other);

	inline const HandDistribution& ipPreflopRange() const
	{
		return ipPreflopRange_;
	}

	inline const HandDistribution& oopPreflopRange() const
	{
		return oopPreflopRange_;
	}

	inline const BetSettings& ipBetSettings() const
	{
		return ipBetSettings_;
	}

	inline const BetSettings& oopBetSettings() const
	{
		return oopBetSettings_;
	}

	inline double allinThreshold() const
	{
		return allinThreshold_;
	}

	inline int initialPot() const
	{
		return initialPot_;
	}

	inline int startingStack() const
	{
		return startingStack_;
	}

	inline const Board& initialBoard() const
	{
		return initialBoard_;
	}

	inline int minimumBetSize() const
	{
		return minimumBetSize_;
	}

	inline Street initialStreet() const
	{
		return initialStreet_;
	}

private:
	HandDistribution ipPreflopRange_;
	HandDistribution oopPreflopRange_;

	Street initialStreet_;
	Board initialBoard_;
	int initialPot_;

	int startingStack_;
	BetSettings ipBetSettings_;
	BetSettings oopBetSettings_;

	int minimumBetSize_;
	double allinThreshold_;
};

} // GameTree

#endif // GAME_TREE_TREE_BUILD_SETTINGS_H