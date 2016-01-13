/**
 * @file unionfind.h
 * @brief Structure of Union-Find Tree。
 */

#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>

/**
 * @brief Union-Find Tree.
 */
struct UnionFind {
	std::vector<int> data;
	/** @param size Number of data */
	UnionFind(int size) : data(size, -1) { }
	/**
	 * @brief  Union data x and y.
	 * @param  x,y Index of data which is united.
	 */
	bool unionSet(int x, int y) {
		x = root(x); y = root(y);
		if (x != y) {
			if (data[y] < data[x]) std::swap(x, y);
			data[x] += data[y]; data[y] = x;
		}
		return x != y;
	}
	/**
	 * @brief Wheather x and y have common root or not.
	 */
	bool findSet(int x, int y) {
		return root(x) == root(y);
	}
	int root(int x) {
		return data[x] < 0 ? x : data[x] = root(data[x]);
	}
	int size(int x) {
		return -data[root(x)];
	}
};

#endif
