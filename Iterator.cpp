#include "iterator"

#include <iostream>
#include <string>

class Node {
	friend class List;
	friend std::ostream& operator << (std::ostream& os, const Node& node);
	std::string name;
	Node* next = nullptr;
	Node(const std::string& n) : name(n) {}
};

std::ostream& operator << (std::ostream& os, const Node& node) {
	os << node.name;
	return os;
}

class List {
	Node* head = nullptr;
	Node* tail = nullptr;
public:
	void Add(const std::string& n) {
		Node * nN = new Node(n);
		if (tail) {
			tail->next = nN;
		}

		tail = nN;

		if (!head) {
			head = tail;
		}
	}

	class Iterator {
		Node* const head;
		Node* current;
	public:
		Iterator(const List& list) : head(list.head), current(list.head) {}
		Iterator & operator++() {
			if (current) {
				current = current->next;
			}
			return *this;
		}
		operator bool() const {
			return current != nullptr;
		}
		const Node& operator*() const {
			return *current;
		}
		void Reset() {
			current = head;
		}
	};

	Iterator GetIterator() {
		return Iterator(*this);
	}
};

void testIterator() {
	List list;

	list.Add("First Node");
	list.Add("Second Node");
	list.Add("Third Node");
	list.Add("Fourth Node");
	list.Add("Fifth Node");

	auto it = list.GetIterator();

	if (it) {
		do {		
			std::cout << *it << "\n";		
		} while (++it);
	}
}