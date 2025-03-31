#pragma once

template <typename T>
class LinkedList {
private:
	T val;
	LinkedList& next;
public:
	LinkedList(T val) : val(val), last(nullptr), first(this) {}

	void append(T val);

	LinkedList& get_last();
};
