#ifndef ARRAY_2D__T_H_
#define ARRAY_2D__T_H_

#include <vector>

template <typename T>
class Array2D_T
{
public:
	Array2D_T(const int xSize, const int ySize):
		xSize(xSize),
		ySize(ySize),
		values(xSize * ySize)
	{
		values.reserve(xSize * ySize);
	}

	Array2D_T(const int xSize, const int ySize, const T& fillValue):
		xSize(xSize),
		ySize(ySize),
		values(xSize * ySize, fillValue)
	{
	}

	T GetValue(const int xIndex, const int yIndex) const
	{
		return values[ComputeIndexFromXAndY(xIndex, yIndex)];
	}

	void SetValue(int xIndex, int yIndex, const T& value)
	{
		values[ComputeIndexFromXAndY(xIndex, yIndex)] = value;
	}

	void Fill(const T& value)
	{
		for (int i = 0; i < values.size(); ++i)
		{
			values[i] = value;
		}
	}

	T* GetRow(const int xIndex)
	{
		return &values[ComputeIndexFromX(xIndex)];
	}

	const T* GetRow(const int xIndex) const
	{
		return &values[ComputeIndexFromX(xIndex)];
	}

private:
	int ComputeIndexFromXAndY(const int xIndex, const int yIndex) const
	{
		return xIndex * ySize + yIndex;
	}

	int ComputeIndexFromX(const int xIndex) const
	{
		return xIndex * ySize;
	}

	std::vector<T> values;
	int xSize;
	int ySize;
};

#endif // ARRAY_2D__T_H_