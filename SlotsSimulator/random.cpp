// SlotsSimulator.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include <stdlib.h>
#include <ctime>
#include <mutex>
#include <intrin.h>

#include "utils.h"

/*
Random number generation utils
*/

//standard generator
void InitG() {  //initialization
	srand((unsigned int)time(NULL));
}
long R(long scope) {
	return (rand() % scope);
}

std::once_flag initRNG;
long SlotRandom::RANDOM(long scope) {  //The randomizing
	std::call_once(initRNG, InitG);
	return (wyhash64()) % scope;
}

SlotRandom::SlotRandom()  //main initialization
{
	wyhash64_x = (((UINT64)rand()) << 32) + (UINT64)rand();
} //

UINT64 SlotRandom::wyhash64() {
	wyhash64_x += 0x60bee2bee120fc15;
	UINT64 tmp_lo, tmp_hi;
	tmp_lo = _umul128(wyhash64_x, 0xa3b195354a39b70d, &tmp_hi);
	UINT64 m1 = tmp_hi ^ tmp_lo;
	tmp_lo = _umul128(m1, 0x1b03738712fad5c9, &tmp_hi);
	UINT64 m2 = tmp_hi ^ tmp_lo;
	return m2;
}

int SlotRandom::random_weighted(int weights[], int total_weight, int length) {
	int r, accum, j;
	r = RANDOM(total_weight);
	accum = 0;
	for (j = 0; j < length; j++) {
		accum += *weights;
		if (r < accum) {
			return j;
		}
		weights++;
	}
	// execution never reaches this line if "total_weight" is correct
	return length - 1;
}
int SlotRandom::random_weighted_val(int values[], int weights[], int total_weight, int length) {
	return values[random_weighted(weights, total_weight, length)];
}
//----------------------------------------------------------------------

void SlotRandom::sample(int length, int sample_size, int tgt[]) {
	int j, k;
	// generate random sample
	for (j = 0; j < sample_size; j++) {
		tgt[j] = j;
	}
	for (; j < length; j++) {
		k = RANDOM(j + 1);
		if (k < sample_size) {
			tgt[k] = j;
		}
	}
	// sort sample
	int km, tmp;
	for (j = 0; j < sample_size - 1; j++) {
		km = j;
		for (k = j + 1; k < sample_size; k++) {
			if (tgt[k] < tgt[km]) {
				km = k;
			}
		}
		if (km != j) {
			tmp = tgt[j];
			tgt[j] = tgt[km];
			tgt[km] = tmp;
		}
	}
}
