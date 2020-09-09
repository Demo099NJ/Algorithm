#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;

int getMedian(const vector<int> &array) {
	int loc(-1);
	int len = (int)array.size();
	switch(len % 2) {
		case 0: loc = len / 2 - 1; break;
		case 1: loc = len / 2; break;
		default: break;
	}
	return array[loc];
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void showArray(vector<int> a) {
	//assert(a != nullptr);
	for(int i = 0; i < (int)a.size(); ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	return;
}

int main() {
	int val(-1);
	vector<int> array;
	while(cin >> val) {
		array.push_back(val);
		int loc = (int)array.size() - 1;
		for(int i = loc - 1; i >= 0; --i) {
			if(array[i] > array[loc]) {
				swap(array[i], array[loc]);
				loc -= 1;
			}
			else {
				break;
			}
		}
		//showArray(array);
		cout << getMedian(array) << " ";
	}
	return 0;
}
