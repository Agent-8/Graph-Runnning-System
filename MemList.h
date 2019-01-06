#pragma once

#include "stdafx.h"

class MemList {
public:
	(vector<matrixsp>)* vals;
	(vector<int>)* freeIndices;
	MemList() {
		vals = new vector<matrixsp>();
		freeIndices = new vector<int>();
	}
	~MemList() {
		delete vals;
		delete freeIndices;
	}

	matrixsp get(int location) {
		return (*vals)[location];
	}

	int mem_alloc() {
		if (freeIndices->size() == 0) {
			vals->push_back(0);
			return vals->size() - 1;
		}
		int ret = (*freeIndices)[0];
		freeIndices->erase(freeIndices->begin());
		return ret;
	}

	bool mem_free(int location) {
		if (location >= vals->size() || location < 0)
			return false;
		freeIndices->push_back(location);
		return true;
	}
};

