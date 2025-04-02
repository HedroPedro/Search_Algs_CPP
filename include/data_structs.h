#pragma once
#include <iostream>
#include <exception>
#include <string>

using std::cerr;

template <typename T>
struct Node {
	T val;
	Node<T>* next;
};

template <typename T, typename U = int>
struct PrioNode {
	T val;
	U prio;
	PrioNode<T>* next;
};

template <typename T = int>
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
			throw -1;
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

template <typename T = int>
class Queue {
private:
	Node<T>* top;
	Node<T>* last;
public:
	virtual void enqueue(T val) {
		Node<T>* no = new Node<T>;
		no->val = val;
		no->next = last;
		if (top == nullptr) {
			top = last = no;
			return;
		}
		last = no;
	}

	virtual T dequeue() {
		if (isEmpty()) {
			cerr << "Queue underflow\n";
			throw -1;
		}
		T val = top->val;
		auto to_free = top;
		top = top->next;
		delete to_free;

		if (top == nullptr) {
			last = nullptr;
		}

		return val;
	}

	virtual bool isEmpty() const {
		return top == nullptr;
	}

	virtual ~Queue() {
		while (!isEmpty()) {
			dequeue();
		}
	}
};

template <typename T = int>
class QueueEx : public Queue<T>{
private:
	Stack<T> front, back;
public:
	QueueEx() : front(nullptr), back(nullptr) {};

	void enqueue(T val) override {
		back.push(val);
	}

	T dequeue() override {
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

	bool isEmpty() const override {
		return back.isEmpty();
	}

	~QueueEx() override {
		while (!back.isEmpty()) {
			back.pop();
		}
	}
};

template <typename T = int>
class PrioQueue : public Queue{
private:
	PrioNode<T>* top;
public:
	PrioQueue() : top(nullptr) {}

	void enqueue(T val) override = 0;

	void enqueue(T val, int prio){
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

	T dequeue() override {
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

	bool isEmpty() const override {
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