#pragma once

/*
Random number generation utils
*/
void InitG();  //initialization

class SlotRandom {
private:
	UINT64 wyhash64_x;
	UINT64 wyhash64();
public:
	SlotRandom();
	long RANDOM(long scope);
	int random_weighted(int weights[], int total_weight, int length);
	int random_weighted_val(int values[], int weights[], int total_weight, int length);
	void sample(int length, int sample_size, int tgt[]);
};

//------------------------------------------

/*
Util functions to read a file ignoring comments
Comments must start from "#", "//" or ";" at the very beginning of a line
*/
void read_int_file(const wchar_t * filename, int * tgt);

void sum_int64_arr(UINT64 dst[], UINT64 term[], UINT64 len);
void max_int64_arr(UINT64 dst[], UINT64 term[], UINT64 len);

/*
 * Array template common functions
 */

template <typename T, size_t N> void fill_arr(T(&arr)[N], const T value) {
	for (int j = 0; j < N; j++) {
		arr[j] = value;
	}
}
template <typename T, size_t N> bool all_equal(const T(&arr)[N], const T value) {
	for (auto elem : arr) {
		if (elem != value) {
			return false;
		}
	}
	return true;
}
