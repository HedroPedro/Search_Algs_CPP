#pragma once
#include <list>
#include <memory>

using std::shared_ptr;

template <int N, typename T>
class Tuple {
public:
	T values[N];
	~Tuple() = default;
};

class Pair2DInt : public Tuple<2, int> {
public:
	Pair2DInt(int x, int y) : values{ x, y } {};

	
};