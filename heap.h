#pragma once
#include <iostream>
#include "Vector.h"

template <typename T> class Heap {
	Vector <T> nodes;

public:
	int size;

	Heap() : size(0) {}

	void siftUp(T v) {
		if (nodes[v >> 1] <= nodes[v])
			return;

		std::swap(nodes[v >> 1], nodes[v]);
		siftUp(v >> 1);
	}

	void siftDown(T v) {
		if ((v << 1) >= size)
			return;

		if ((v << 1) == size - 1) {
			if (nodes[v << 1] < nodes[v]) {
				std::swap(nodes[v << 1], nodes[v]);
			}
		}
		else if (nodes[v << 1] < nodes[(v << 1) + 1] && nodes[v << 1] < nodes[v]) {
			std::swap(nodes[v << 1], nodes[v]);
			siftDown(v << 1);
		}
		else if (nodes[(v << 1) + 1] < nodes[v]) {
			std::swap(nodes[(v << 1) + 1], nodes[v]);
			siftDown((v << 1) + 1);
		}
	}

	T get_min() {
		if (!size) {
			throw std::out_of_range("Heap is empty");
		}

		return nodes[0];
	}

	T extract_min() {
		if (!size) {
			throw std::out_of_range("Heap is empty");
		}

		T res = nodes[0];
		std::swap(nodes[0], nodes[--size]);
		siftDown(0);
		return res;
	}

	int get_size() {
		return size;
	}

	bool is_empty() {
		return !size;
	}

	void insert(int a) {
		nodes.push_back(a);
		siftUp(size++);
	}

	T * pointer_insert(int a) {
		nodes.push_back(a);
	}

	void resize(int n) {
		nodes.resize(n);
		size = n;
	}

	void construct(T * begin, T * end) {
		size = end - begin + 1;
		this->resize(size);
		for (int j = size - 1; j >= 0; j--) {
			nodes[j] = end[j - size + 1];
			siftDown(j);
		}
	}

	~Heap() {
	}
};