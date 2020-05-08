#ifndef HAND_DISTRIBUTION_H_
#define HAND_DISTRIBUTION_H_

#include "Hand.h"

class HandDistribution
{
public:
	/**
	  * @param str: hand range with piosolver formatting, e.g., "AA,AKs:0.5,KQo,77:0.2"
	 */
	HandDistribution(const std::string& str);
	HandDistribution(const std::vector<Hand>& hands);
	HandDistribution(std::vector<Hand>&& hands);

	const Hand& operator[] (const int index) const;

	std::vector<Hand>::const_iterator begin() const;
	std::vector<Hand>::const_iterator end() const;

	inline const std::vector<Hand>& hands() const
	{
		return hands_;
	}

	inline std::vector<Hand>& hands()
	{
		return hands_;
	}

	std::size_t size() const;

private:
	std::vector<Hand> hands_;
};

#endif // HAND_DISTRIBUTION_H_