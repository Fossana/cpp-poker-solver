#include "HandDistribution.h"
#include <sstream>

HandDistribution::HandDistribution(const std::string& str)
{
	std::istringstream ss(str);
	std::string token;

	while (getline(ss, token, ','))
	{
		Rank rank1 = RankFromChar(token.at(0));
		Rank rank2 = RankFromChar(token.at(1));

		for (Suit suit1 : suits)
		{
			for (Suit suit2 : suits)
			{
				if (token.length() == 2)
				{
					if (rank1 == rank2 && suit1 >= suit2)
					{
						continue;
					}
				}
				else if (token.at(2) == ':')
				{
					if (rank1 == rank2 && suit1 >= suit2)
					{
						continue;
					}
				}
				else if (token.at(2) == 's')
				{
					if (suit1 != suit2)
					{
						continue;
					}
				}
				else if (token.at(2) == 'o')
				{
					if (suit1 == suit2)
					{
						continue;
					}
				}

				Card card1(rank1, suit1);
				Card card2(rank2, suit2);
				Hand hand(card1, card2);
				hands_.push_back(hand);
			}
		}
	}
}

HandDistribution::HandDistribution(const std::vector<Hand>& hands):
	hands_(hands)
{
}

HandDistribution::HandDistribution(std::vector<Hand>&& hands):
	hands_(std::move(hands))
{
}

std::vector<Hand>::const_iterator HandDistribution::begin() const
{
	return hands_.begin();
}

std::vector<Hand>::const_iterator HandDistribution::end() const
{
	return hands_.end();
}

const Hand& HandDistribution::operator[] (const int index) const
{
	return hands_[index];
}

std::size_t HandDistribution::size() const
{
	return hands_.size();
}
