#include <set>
#include <iostream>
#include "pch.h"
#include "../SuperNova/heap.h"

int get_rand() {
	return (rand() << 15) ^ rand();
}

TEST(TestCaseName, TestName) {
	Heap <int> h;
	h.insert(5);
	h.insert(3);
	h.insert(3);
	EXPECT_EQ(3, h.extract_min());
	EXPECT_EQ(3, h.extract_min());
	EXPECT_EQ(1, h.size);
}

TEST(sample, sample) {
	Vector <int> h;
	EXPECT_EQ(true, h.empty());
}

TEST(vector, vector) {
	Vector <int> a;
	for (int i = 0; i < 1000000; i++) {
		a.push_back(i);
	}
	for (int i = 0; i < 1000000; i++) {
		a.pop_back();
	}
	EXPECT_EQ(a.empty(), true);

}

TEST(First, Emptiness) {
	Heap <int> h;
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < (j + 1) * 100; i++) {
			h.insert(j);
		}
		for (int i = 0; i < (j + 1) * 100; i++) {
			h.extract_min();
		}
		EXPECT_EQ(true, h.is_empty());
	}
}

TEST (Second, CheckMin) {
	std::multiset <int> ms;
	Heap <int> h;
	int q = 10000;
	while (q--) {
		int x = get_rand();
		h.insert(x);
		ms.insert(x);
		EXPECT_EQ(h.get_min(), *ms.begin());
	}
}

TEST(Third, Strong) {
	int q = 1000000;
	std::multiset <int> ms;
	Heap <int> h;
	while (q--) {
		int x, y;
		if (!x) {
			y = get_rand();
			ms.insert(y);
			h.insert(y);
		}
		else if (x == 1) {
			if (h.is_empty())
				continue;
			EXPECT_EQ(*ms.begin(), h.extract_min());
			ms.erase(ms.begin());
		}
		else if (x == 2) {
			if (h.is_empty())
				continue;
			EXPECT_EQ(*ms.begin(), h.get_min());
		}
	}
}