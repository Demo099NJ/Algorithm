#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

string *get_array(int len) {
	string *a = new string[len];	assert(a != nullptr);
	for(int i = 0; i < len; ++i) {
		cin >> a[i];
	}
	return a;
}

void release_array(string a[], int len) {
	if(a == nullptr) {
		return;
	}
	delete[]a;
}

void show_array(string a[], int len) {
	if(a == nullptr) {
		return;
	}
	for(int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	return;
}

void swap(string &x, string &y) {
	string temp = x;
	x = y;
	y = temp;
}

void quickSort(string a[], int len, int first, int last) {
	if(first < last) {
		string pivot = a[last];
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

void select_elements(string a[], int len, int k) {
	int median = (len % 2 == 0) ? (len / 2) : (len / 2 + 1);
	median -= 1;
	int begin = median - k;
	cout << a[begin];
	for(int i = 1; i < 2 * k + 1; ++i) {
		cout << " " << a[i + begin];
	}
	cout << endl;
}

int main() {
	int len(0), k(0);
	cin >> len >> k;
	string *array = get_array(len);
	quickSort(array, len, 0, len - 1);
	show_array(array, len);
	select_elements(array, len, k);
	release_array(array, len);
	return 0;
}
