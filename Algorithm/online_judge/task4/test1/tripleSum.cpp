#include<iostream>
#include<assert.h>
#include<math.h>
using namespace std;

int *get_array(int len) {
	int *array = new int[len];	assert(array != nullptr);
	for(int i = 0; i < len; ++i) {
		cin >> array[i];
	}
	return array;
}

void show_array(int a[], int len) {
	if(a == nullptr) {
		return;
	}
	for(int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	return;
}

void release(int *a, int len) {
	assert(a != nullptr);
	delete[]a;
}

void swap(int &x, int &y) {
	int temp = x;	x = y;	y = temp;
	return;
}

void quickSort(int a[], int len, int first, int last) {
	if(first < last) {
		int pivot = a[last];
		int i = first - 1;
		for(int j = first; j < last; ++j) {
			if(a[j] < pivot) {
				++i;
				swap(a[i], a[j]);
			}
		}
		swap(a[i + 1], a[last]);
		int temp = i + 1;

		quickSort(a, len, first, temp - 1);
		quickSort(a, len, temp + 1, last);
	}
	return;
}

void bubbleSort(int a[], int len) {
	for(int i = 0; i < len; ++i) {
		for(int j = 0; j < (len - i); ++j) {
			if(a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}
	return;
}

int find_pair_sum(int a[], int len, int tar, int exce) {
	int first(0), second(1), closed(0x7fffffff);
	for(int i = 0; i < len - 1; ++i) {
		if(fabs(tar - (a[i] + a[i + 1])) < closed){
			first = i;
			second = i + 1;
			closed = fabs(tar - (a[i] + a[i + 1]));
		}
	}
	// find pair
	int sum(0);
	while(first >= 0 && second < len) {
		int result = a[first] + a[second];
		if(result == tar) {
			//printf("a triple: a[%d] = %d, a[%d] = %d, a[%d] = %d;\n",	first, a[first], second, a[second], exce, a[exce]);
			if(first != exce && second != exce) {
				// avoid "exce"
				sum += 1;
			}
			first -=1;
			second += 1;
		}
		else if(result > tar) {
			first -=1;
		}
		else if(result < tar) {
			second += 1;
		}
	}
	return sum;
}

int find_triple_sum(int a[], int len, int tar) {
	int result(0);
	// nlogn
	//quickSort(a, len, 0, len - 1);
	bubbleSort(a, len);
	show_array(a, len);
	// n * n
	for(int i = 0; i < len; ++i) {
		result += find_pair_sum(a, len, tar - a[i], i);
	}
	return result;
}

int main() {
	int len(0), target(0);
	cin >> len >> target;
	int *array = get_array(len);
	//show_array(array, len);
	cout << find_triple_sum(array, len, target) / 3 << endl;
	release(array, len);
	return 0;
}
