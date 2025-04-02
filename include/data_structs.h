#pragma once
#include <iostream>
#include <exception>
#include <string>

using std::cerr;
using uint = unsigned int;

template <typename T>
struct Node {
	T val;
	Node<T>* next;
};

template <typename T>
struct PrioNode {
	uint prio;
	T val;
	PrioNode<T>* next;
};

template <typename T>
class Stack {
private:
	Node<T>* top;
public:
	Stack() : top(nullptr) {}

	void push(T val) {
		Node<T> *no = new Node<T>;
		no->val = val;
		no->next = top;
		top = no;
	}

	T pop() {
		if (isEmpty()) {
			cerr << "Stack overflow\n";
			throw - 1;
		}

		auto val = top->val;
		auto to_free = top;
		top = top->next;
		delete to_free;
		return val;
	}

	T peek() {
		if (isEmpty()) {
			cerr << "Stack empty\n";
			throw - 1;
		}
		return top->val;
	}

	bool isEmpty() const {
		return top == nullptr;
	}


	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	};

	void reverse() {
		Stack<T> tmp;

		while (!isEmpty()) {
			tmp.push(pop());
		}

		auto ptr = tmp.top;

		while (ptr != nullptr) {
			push(ptr->val);
			ptr = ptr->next;
		}
	}
};

template <typename T>
class Queue {
private:
	Stack<T> front, back;
public:
	Queue() : front(nullptr), back(nullptr) {};

	void enqueue(T val) {
		back.push(val);
	}

	T dequeue() {
		T val;
		while (!back.isEmpty()) {
			front.push(back.pop());
		}

		val = front.pop();

		while (!front.isEmpty()) {
			back.push(front.pop());
		}

		return back;
	}

	bool isEmpty() const {
		return back.isEmpty();
	}

	~Queue() {
		while (!back.isEmpty()) {
			back.pop();
		}
	}
};

template <typename T>
class PrioQueue {
private:
	PrioNode<T>* top;
public:
	PrioQueue() : top(nullptr) {}

	void enqueue(T val, uint prio) {
		PrioNode<T>* prev = nullptr;
		auto atual = top;
		while (atual != nullptr && atual->prio > prio) {
			prev = atual;
			atual = atual->next;
		}
		PrioNode<T> *no = new PrioNode<T>;
		no->val = val;
		no->prio = prio;
		no->next = atual;
		if (prev == nullptr) {
			top = no;
			return;
		}

		prev->next = no;
	}

	T dequeue() {
		if (isEmpty()) {
			cerr << "Queue empty\n";
			throw -1;
		}

		auto val = top->val;
		auto to_free = top;
		top = top->next;
		delete to_free;

		return val;
	}

	bool isEmpty() const {
		return top == nullptr;
	}
};

bool is_balanced(std::string& str) {
	Stack<char> stack;

	for (auto chr : str) {
		if (chr == '(' || chr == '[' || chr == '{') {
			stack.push(chr);
			continue;
		}
		if (chr == ')') {
			if (stack.pop() != '(')
				return false;
		}

		if (chr == ']') {
			if (stack.pop() != '[')
				return false;
		}

		if (chr == '}') {
			if (stack.pop() != '{')
				return false;
		}
	}

	return stack.isEmpty();
}
