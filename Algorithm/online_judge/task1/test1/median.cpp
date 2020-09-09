#include<iostream>
#include<assert.h>
using namespace std;

//int sum(0);

int *getArray(int len) {
	int *array = new int[len];	assert(array != nullptr);
	for(int i = 0; i < len; ++i) {
		cin >> array[i];
	}
	return array;
}

void release(int *a, int len) {
	assert(a != nullptr);
	delete[]a;
}

void swap(int &x, int &y) {
	int temp = x;	x = y;	y = temp;
	return;
}

//use quick sort
void mySort(int a[], int len, int first, int last) { 
	//++sum;	assert(sum < 10);
	// judge if we should stop
	if(first >= last) { return; }
	// quick sort
	int temp = a[first];
	int head(first), tail(last);
	//for(int i = 0; i < last - first; ++i) {
	while(head < tail) {
		//int i = head;
		for(; head < tail; ++head) {
			if(temp < a[head]) { break; }
			else if(temp >= a[head]) { continue; }
		}
		if(head >= tail) { break; }
		// else, do:
		for(; head < tail; --tail) {
			if(temp > a[tail]) {
				swap(a[head], a[tail]);
				//cout << "first = " << first << ", last = " << last << endl;
				break;
			}
			else if(temp <= a[tail]) { continue; }
		}
		printf("head = %d, tail = %d\n", head, tail);
	}
	int mid = head;
	printf("first = %d, mid = %d, last = %d\n", first, mid, last);
	//fixed
	swap(a[first], a[mid - 1]);
	//recursion
	mySort(a, len, first, mid);
	mySort(a, len, mid + 1, last);
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

void showArray(int a[], int len) {
	for(int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	return;
}

void selectElement(int a[], int len, int k) {
	int mid(0);
	switch(len % 2) {
		case 0: mid = len / 2 - 1; break;
		case 1: mid = len / 2; break;
		default: break;
	}
	int start = mid - k;	assert(start >= 0);
	for(int i = 0; i < 2 * k + 1; ++i) {
		assert((i + start) < len);
		printf("%d ", a[i + start]);
	}
	cout << endl;
	return;
}

int main() {
	// get two key numbers
	int k(0), len(0);
	cin >> k >> len;

	// get array and handle the problem
	int *list = getArray(len);
	//showArray(list, len);
	//mySort(list, len, 0, len - 1); //cout << "the sum: " << sum << endl;
	quickSort(list, len, 0, len - 1);
	selectElement(list, len, k);

	//release
	//release(list, len);
	//showArray(list, len);
	return 0;
}
