#include "TreeBuildSettings.h"

namespace GameTree
{

TreeBuildSettings::TreeBuildSettings(
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
):
	ipPreflopRange_(ipPreflopRange),
	oopPreflopRange_(oopPreflopRange),
	initialStreet_(initialStreet),
	initialBoard_(initialBoard),
	initialPot_(initialPot),
	startingStack_(startingStack),
	ipBetSettings_(ipBetSettings),
	oopBetSettings_(oopBetSettings),
	minimumBetSize_(minimumBetSize),
	allinThreshold_(allinThreshold)
{
}

TreeBuildSettings::TreeBuildSettings(const TreeBuildSettings& other):
	ipPreflopRange_(other.ipPreflopRange_),
	oopPreflopRange_(other.oopPreflopRange_),
	initialStreet_(other.initialStreet_),
	initialBoard_(other.initialBoard_),
	initialPot_(other.initialPot_),
	startingStack_(other.startingStack_),
	ipBetSettings_(other.ipBetSettings_),
	oopBetSettings_(other.oopBetSettings_),
	minimumBetSize_(other.minimumBetSize_),
	allinThreshold_(other.allinThreshold_)
{
}

} // GameTree