#include "sort.h"
using namespace std;

void swap(int &x, int &y) {
	int temp = x;	x = y;	y = temp;
	return;
}

void quickSort(int a[], int len, int first, int last) {
	//cout << "emmmm" << endl;
	if(first < last) {
		int pivot = a[last];
		int i = first - 1;
		for(int j = first; j < last; ++j) {
			//cout << "lalala" << endl;
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
