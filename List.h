#pragma once

template <typename T> class List {
public:
	List * next;
	T value;

	List() : next(NULL) {}
	List(T value) : next(NULL), value(value) {}
	List(T value, List * next) : next(next), value(value) {}

	void insert(List * element) {
		element->next = next;
		next = element;
	}

	void insert(int pos, List * element) {
		List * current = this;
		for (int j = 0; j < pos; ++j) {
			if (!current) {
				return void(throw(std::logic_error));
			}
			current = current->next;
		}
		insert(current, element);
	}

	void push_back(List * element) {
		List * current = this;
		while (current->next) {
			current = current->next;
		}
		current->next = element;
	}

	void erase() {
		List * element = next;
		next = element->next;
		delete element;
	}

	void erase(int pos) {
		List current = this;
		for (int j = 0; j < pos; ++j) {
			current = current->next;
		}
		erase(current);
	}
	~List() {
		
	 }
};