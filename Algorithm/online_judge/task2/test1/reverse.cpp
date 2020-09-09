#include<iostream>
#include<assert.h>
using namespace std;

char **getArray(int len, int col) {
	char **array = new char*[len];	assert(array != nullptr);
	for(int i = 0; i < len; ++i) {
		array[i] = new char[col];	assert(array[i] != nullptr);
	}
	for(int i = 0; i < len; ++i) {
		for(int j = 0; j < col; ++j) {
			cin >> array[i][j];
		}
	}
	return array;
}

void releaseArray(char **array, int len, int col) {
	assert(array != nullptr);
	for(int i = 0; i < len; ++i) {
		assert(array[i] != nullptr);
		delete[]array[i];
	}
	delete[]array;
}

// if the dictionary order of a[] is greater than b[], return TRUE
// else, not greater, return FALSE
bool strGreater(char a[], int lenA, char b[], int lenB) {
	for(int i = 0; i < lenA && i < lenB; ++i){
		if(a[i] > b[i]) { return true; }
		else if(a[i] < b[i]) { return false; }
		// else if(a[i] == b[i]) { compare next character;}
	}
	// now, part of a[] is the same as part of b[]
	return (lenA > lenB);
}

long int sumReverse(char **array, int len, int col) {
	long int ret(0);
	for(int i = 0; i < len - 1; ++i) {
		for(int j = i + 1; j < len; ++j) {
			if(strGreater(array[i], col, array[j], col)) {
				++ret;
			}
		}
	}
	return ret;
}

int main() {
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	int len(0);
	cin >> len;
	char **array = getArray(len, 10);
	long int result = sumReverse(array, len, 10);
	cout << result << endl;
	releaseArray(array, len, 10);
	return 0;
}
