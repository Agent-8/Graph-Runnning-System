// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <cassert>
#include <bitset>
#include <vector>
#include <algorithm>
#include <memory>
#include <gmpxx.h>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

typedef Matrix<mpz_class, Dynamic, Dynamic> MatrixXz;
typedef Matrix<mpz_class, Dynamic, 1> VectorXz;

static inline void operator%=(MatrixXz& inp, const mpz_class modby) {
	assert(modby > 0);
	for (int i = 0; i < inp.rows(); i++) {
		for (int j = 0; j < inp.cols(); j++) {
			mpz_class ret = inp(i, j) % modby;
			inp(i, j) = ret >= 0 ? ret : ret + modby;
		}
	}
}

static inline void operator%=(VectorXz& inp, const mpz_class modby) {
	assert(modby > 0);
	for (int i = 0; i < inp.size(); i++) {
		mpz_class ret = inp(i) % modby;
		inp(i) = ret >= 0 ? ret : ret + modby;
	}
}

typedef shared_ptr<MatrixXz> matrixsp;
typedef shared_ptr<VectorXz> vecsp;
typedef shared_ptr<VectorXi> intvecsp;
typedef unique_ptr<MatrixXz> matrixup;
typedef unique_ptr<VectorXz> vecup;
typedef shared_ptr<vector<matrixsp>> matrixList;
//typedef vector<int> vec;

inline int twoPower(int n) { return 1 << (n % 32); }
inline int numTwoPower(int num, int power) { return num << (power % 32); }
inline int numTwoNegPower(int num, int power) { return num >> (power % 32); }

inline int roundNum(int n) { return (int)(n + 0.5); }

// TODO: reference additional headers your program requires here