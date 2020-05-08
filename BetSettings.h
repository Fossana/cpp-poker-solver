#ifndef GAME_TREE_BET_SETTINGS_H_
#define GAME_TREE_BET_SETTINGS_H_

#include <vector>

namespace GameTree
{

class BetSettings
{
public:
	BetSettings(
		const std::vector<double>& flopBetSizes,
		const std::vector<double>& turnBetSizes,
		const std::vector<double>& riverBetSizes,
		const std::vector<double>& flopRaiseSizes,
		const std::vector<double>& turnRaiseSizes,
		const std::vector<double>& riverRaiseSizes
	);
	BetSettings(const BetSettings& other);

	inline const std::vector<double>& flopBetSizes() const
	{
		return flopBetSizes_;
	}

	inline const std::vector<double>& turnBetSizes() const
	{
		return turnBetSizes_;
	}

	inline const std::vector<double>& riverBetSizes() const
	{
		return riverBetSizes_;
	}

	inline const std::vector<double>& flopRaiseSizes() const
	{
		return flopRaiseSizes_;
	}

	inline const std::vector<double>& turnRaiseSizes() const
	{
		return turnRaiseSizes_;
	}

	inline const std::vector<double>& riverRaiseSizes() const
	{
		return riverRaiseSizes_;
	}

private:
	std::vector<double> flopBetSizes_;
	std::vector<double> turnBetSizes_;
	std::vector<double> riverBetSizes_;

	std::vector<double> flopRaiseSizes_;
	std::vector<double> turnRaiseSizes_;
	std::vector<double> riverRaiseSizes_;
};

} // GameTree

#endif // GAME_TREE_BET_SETTINGS_H_