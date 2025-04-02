#include "main.h"

using namespace std;

int main() {
	Stack<int> stck;
	stck.push(1);
	stck.push(2);
	stck.push(3);

	stck.reverse();

	PrioQueue<int> queue;
	queue.enqueue(0, 9);
	queue.enqueue(1, 10);
	queue.enqueue(10, 0);

	cout << queue.dequeue() << '\n';
	cout << queue.dequeue() << '\n';
	cout << queue.dequeue() << '\n';
	return 0;
}
