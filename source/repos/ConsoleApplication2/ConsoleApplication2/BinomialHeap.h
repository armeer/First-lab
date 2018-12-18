#pragma once
#include "Vector.h"
#include <vector>
#include "List.h"

using std::cout;

template <typename T> class BinomialHeap;

template <typename T> class tree {
public:

	friend class BinomialHeap<T>;

	T value;
	int degree;
	List <tree <T> * > * start, * end;
	tree * parent = nullptr;

	tree() : start(new List <tree <T> * >), degree(0), end(start) {}
	tree(T value) : start(new List <tree <T> * >), value(value), degree(0), end(start) {}

};

template <typename T> class BinomialHeap {
private:
	T value;
	List <tree <T> *> * start, * end;

public:

	BinomialHeap() : start(new(List <tree <T> * >)), end(nullptr) {}
	BinomialHeap(T value) : value(value) {
		start = new List <tree <T> * >;
		auto tmp = new tree <T> (value);
		end = new List <tree <T> * >(tmp);
		start->next = end;
	}
	BinomialHeap(List <tree <T> * > * trees) : start(trees), end(nullptr) {
		if (!start)
			start = new List <tree <T> * >;


		end = start;

		while (end->next) {
			if (end == start)
				value = end->next->value->value;
			end = end->next;
			if (end->value->value < value)
				value = end->value->value;
		}
	}
	
	bool is_empty() {
		return !start->next;
	}

	void show_first_row() {
		auto tmp = start->next;
		while (tmp) {
			cout << tmp->value->value << ' ';
			tmp = tmp->next;
		}
		cout << " list\n";
	}
	
	T get_min() {
		//if (is_empty())
			//throw(std::logic_error("sdfsf"));
		return value;
	}

	void merge_trees(tree <T>  * & t1, tree <T> * & t2) {

		if (t1->value > t2->value)
			std::swap(t1, t2);
		t2->parent = t1;
		t1->end->insert(t2);
		t1->end = t1->end->next;
		++t1->degree;
	}

	void merge(BinomialHeap <T> * AddedHeap) {
		
		List <tree <T> * > * curOld = start->next, * curNew = AddedHeap->start->next, * prev = start;


		while (curOld && curNew) {
			if (curNew->value->degree < curOld->value->degree) {
				List <tree <T> *> * tmp = curNew->next;
				prev->insert(curNew);
				prev = curNew;
				curNew = tmp;
				//delete curNew;
			}
			else if (curNew->value->degree == curOld->value->degree) {
				merge_trees(curOld->value, curNew->value);
				while (curOld->next && curOld->next->value->degree == curOld->value->degree) {
					merge_trees(curOld->value, curOld->next->value);
					curOld->erase();
				}
				auto tmp = curNew;
				delete curNew;
				curNew = tmp->next;
			}
			else {
				prev = curOld;
				curOld = curOld->next;
			}
		}
		if (!curOld)
			prev->next = curNew;

		auto tmp = start->next;
		if (tmp)
			value = tmp->value->value;
		while (tmp) {
			if (value > tmp->value->value)
				value = tmp->value->value;
			tmp = tmp->next;
		}
	}

	void insert(T value) {
		BinomialHeap <T> * AddedElement = new BinomialHeap <T> (value);
		merge(AddedElement);
	}

	T extract_min() {
		T answer = value;
		auto tmp = start->next, prev = start;
		if (!tmp)
			throw std::logic_error("Heap is empty");

		while (tmp->value->value != answer) {
			std::cout << tmp->value->value << ' ';
			prev = tmp;
			tmp = tmp->next;
		}
		std::cout << " row\n";

		BinomialHeap <T> * newHeap = new BinomialHeap(tmp->value->start);
		delete tmp->value;
		prev->erase();

		tmp = start->next;

		if (tmp)
			value = tmp->value->value;

		while (tmp) {
			if (value > tmp->value->value)
				value = tmp->value->value;
			tmp = tmp->next;
		}
		merge(newHeap);
		delete newHeap;
		return answer;
	}
};