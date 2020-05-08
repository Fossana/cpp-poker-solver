#ifndef ARRAY_3D__T_H_
#define ARRAY_3D__T_H_

#include <vector>

template <typename T>
class Array3D_T
{
public:
	Array3D_T(const int xSize, const int ySize, const int zSize):
		xSize(xSize),
		ySize(ySize),
		zSize(zSize),
		values(xSize * ySize * zSize)
	{
	}

	Array3D_T(const int xSize, const int ySize, const int zSize, const T& fillValue):
		xSize(xSize),
		ySize(ySize),
		zSize(zSize),
		values(xSize * ySize * zSize, fillValue)
	{
	}

	T GetValue(const int xIndex, const int yIndex, const int zIndex) const
	{
		return values[ComputeIndexFromXYZ(xIndex, yIndex, zIndex)];
	}

	void SetValue(const int xIndex, const int yIndex, const int zIndex, const T& value)
	{
		values[ComputeIndexFromXYZ(xIndex, yIndex, zIndex)] = value;
	}

	void Fill(const T& value)
	{
		for (int i = 0; i < values.size(); ++i)
		{
			values[i] = value;
		}
	}

	T* operator()(const int xIndex)
	{
		return &values[ComputeIndexFromX(xIndex)];
	}

	const T* operator()(const int xIndex) const
	{
		return &values[ComputeIndexFromX(xIndex)];
	}

	T* operator()(const int xIndex, const int yIndex)
	{
		return &values[ComputeIndexFromXY(xIndex, yIndex)];
	}

	const T* operator()(const int xIndex, const int yIndex) const
	{
		return &values[ComputeIndexFromXY(xIndex, yIndex)];
	}

private:
	int ComputeIndexFromXYZ(const int xIndex, const int yIndex, const int zIndex) const
	{
		return ComputeIndexFromXY(xIndex, yIndex) + zIndex;
	}

	int ComputeIndexFromXY(const int xIndex, const int yIndex) const
	{
		return ComputeIndexFromX(xIndex) + yIndex * zSize;
	}

	int ComputeIndexFromX(const int xIndex) const
	{
		return xIndex * ySize * zSize;
	}

	std::vector<T> values;
	int xSize;
	int ySize;
	int zSize;
};

#endif // ARRAY_3D__T_H_