#include <iostream>
#include <stdexcept>
#include <string>

struct Node {
	int data;
	Node *next;
};

struct Queue {
	Node *head, *tail;
	Queue() { // Initialize empty queue
		head = tail = 0;
	}

	bool is_empty() { return !head; }
	void push(int data) {
		Node *new_node = new Node;
		new_node -> data = data;
		new_node -> next = 0;
		if(is_empty()) head = tail = new_node;
		else {
			tail -> next = new_node;
			tail = tail -> next;
		}
	}
	int front() {
		if(!head) throw std::out_of_range("Queue is empty");
		return head -> data;
	}
	void pop() {
		if(!head) throw std::out_of_range("Queue is empty");
		Node *tmp = head;
		head = head -> next;
		delete tmp;
	}
};

int main() {
	std::string command;
	int data;
	Queue q;
	while (std::cin >> command) {
		try {
			if (command == "push"){
				std::cin >> data;
				q.push(data);
			}
			else if (command=="front") std::cout << q.front() << std::endl;
			else if (command=="pop") q.pop();
			else if (command=="is_empty") std::cout << q.is_empty() << std::endl;
		}
		catch (const std::out_of_range &e){
			std::cout << "Operation failed: empty queue" << std::endl;
		}
	}
	return 0;
}

