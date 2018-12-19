#pragma once
#include <iostream>

int min (int a, int b) {
	return a < b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}

template <typename T> class Vector {
	int size_, back_;
	T * arr;
	const int alpha = 2, betta = 4;

	void upd_size() {
		if ((back_ + 1) * betta >= size_ && back_ < size_)
			return;
		T * new_arr = NULL;

		if ((back_ + 1) * betta < size_) {
			size_ /= alpha;
			new_arr = new T[size_];
		}
		else 
		{
			size_ *= alpha;
			new_arr = new T[size_];
		}

		for (int j = 0; j <= back_; j++) {
			*(new_arr + j) = *(arr + j);
		}

		delete [] arr;
		arr = new_arr;
	}

public:

	Vector () : size_(1), arr(new T[1]), back_(0) {}
	Vector (int size) : size_(size), arr(new T[size]), back_(size - 1) {}
	Vector(int size, T val) : size_(size), arr(new T[size]), back_(size - 1) {
		for (int j = 0; j < size; j++) {
			arr[j] = T;
		}
	}
	Vector(const Vector & v) {
		this->back_ = v.back_;
		this->size_ = v.size_;
		this->arr = new T[v.size_];
		for (int j = 0; j <= back_; j++) {
			this->arr[j] = v.arr[j];
		}
	}

	void push_back (T val) {
		arr[back_++] = val;
		upd_size();
	}

	bool empty() {
		return !back_;
	}

	void pop_back() {
		--back_;
		back_ = max(back_, 0);
		upd_size();
	}

	void resize (int n) {
		T * new_arr = new T[n];
		size_ = n;
		back_ = min(n - 1, size_);
		for (int j = 0; j <= back_; j++) {
			new_arr[j] = arr[j];
		}
		delete [] arr;
		arr = new_arr;
	}

	int size() {
		return size_;
	}

	T & operator [] (int i) {
		return arr[i];
	}

	const T & operator [] (int i) const {
		return arr[i];
	}

	~Vector () {
		delete [] arr;
	}
};