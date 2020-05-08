#include "BetSettings.h"

namespace GameTree
{

BetSettings::BetSettings(
	const std::vector<double>& flopBetSizes,
	const std::vector<double>& turnBetSizes,
	const std::vector<double>& riverBetSizes,
	const std::vector<double>& flopRaiseSizes,
	const std::vector<double>& turnRaiseSizes,
	const std::vector<double>& riverRaiseSizes
):
	flopBetSizes_(flopBetSizes),
	turnBetSizes_(turnBetSizes),
	riverBetSizes_(riverBetSizes),
	flopRaiseSizes_(flopRaiseSizes),
	turnRaiseSizes_(turnRaiseSizes),
	riverRaiseSizes_(riverRaiseSizes)
{
}

BetSettings::BetSettings(const BetSettings& other):
	flopBetSizes_(other.flopBetSizes_),
	turnBetSizes_(other.turnBetSizes_),
	riverBetSizes_(other.riverBetSizes_),
	flopRaiseSizes_(other.flopRaiseSizes_),
	turnRaiseSizes_(other.turnRaiseSizes_),
	riverRaiseSizes_(other.riverRaiseSizes_)
{
}

} // GameTree