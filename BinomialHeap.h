#pragma once
#include "Vector.h"
#include <vector>
#include "List.h"

template <typename T> class BinomialHeap;

template <typename T> class tree {
public:

	friend class BinomialHeap<T>;

	T value;
	int degree;
	List <tree <T> * > * start, * end;
	tree * parent = nullptr;

	tree() : start(new List <tree <T> * >), degree(0) {}
	tree(T value) : start(new List <tree <T> * >), value(value), degree(0) {}

};

template <typename T> class BinomialHeap {
private:
	T value;
	List <tree <T> *> * start, * end;

public:

	BinomialHeap() : start(new(List <tree <T> * >)), end(NULL) {}
	BinomialHeap(T value) : value(value) {
		start = new List <tree <T> * >;
		auto tmp = new tree <T> (value);
		end = new List <tree <T> * >(tmp);
		start->next = end;
	}
	BinomialHeap(List <tree <T> * > * trees) {
		start = trees;
		value = start->value->value;
		end = start;
		while (end->next) {
			end = end->next;
			if (end->value->value < value)
				value = end->value->value;
		}
	}
	
	bool is_empty() {
		return !start->next;
	}

	T get_min() {
		if (!end)
			return std::logic_error;
		return value;
	}

	void merge_trees(tree <T>  * & t1, tree <T> * & t2) {
		t2->parent = t1;
		t1->end->insert(t2);
		t1->end = t2;
		if (t1->value > t2->value) {
			swap(t1->value, t2->value);
		}
		++t1->degree;
	}

	void merge(BinomialHeap <T> * AddedHeap) {
		
		List <tree <T> * > * curOld = start->next, * curNew = AddedHeap->start->next, * prev = start;

		while (curOld && curNew) {
			if (curNew->value->degree < curOld->value->degree) {
				List <tree <T> *> * tmp = curNew;
				prev->insert(tmp);
				tmp = curNew;
				delete curNew;
				prev = tmp;
				curNew = tmp->next;
			}
			else if (curNew->value->degree == curOld->value->degree) {
				merge_trees(curOld->value, curNew->value);
				while (curOld->next && curOld->next->value->degree == curOld->value->degree) {
					merge_trees(curOld->value, curOld->next->value);
					curOld->erase();
				}
				prev = curOld;
				curOld = curOld->next;
				auto tmp = curNew;
				delete curNew;
				curNew = tmp->next;
			}
			else {
				curOld = curOld->next;
			}
		}
		while (curNew) {
			auto tmp = curNew;
			prev->insert(tmp);
			tmp = curNew;
			delete curNew;
			curNew = tmp->next;
		}

	}

	void insert(T value) {
		BinomialHeap <T> * AddedElement = new BinomialHeap(value);
		merge(AddedElement);
		delete AddedElement;
	}

	void extract_min() {
		T answer = value;
		auto tmp = start->next, prev = start;
		if (!tmp)
			return void(throw(std::logic_error));

		while (tmp->value->value != value) {
			prev = tmp;
			tmp = tmp->next;
		}
		BinomialHeap <T> * newHeap = new BinomialHeap(tmp->value->start);
		delete tmp->value;
		prev->erase();
		merge(newHeap);
		return answer;
	}
};