#include<iostream>
#include<assert.h>
#include<cmath>
#include<vector>
using namespace std;

int *getArray(int &len) {
	cin >> len;
	int *a = new int[len];	assert(a != nullptr);
	for(int i = 0; i < len; ++i) {
		cin >> a[i];
	}
	return a;
}

void relase(int a[], int len) {
	assert(a != nullptr);
	delete[]a;
}

void showArray(int a[], int len) {
	assert(a != nullptr);
	for(int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
	return;
}

void searchPair(int a[], int len, int tar) {
	// find a adjacent pair that the sum is the closest to the target value
	int min_dif(0x7fffffff), sum(0); //cout << Atar << endl;
	int loc(-1);
	for(int i = 0; i < (len - 1); ++i) {
		sum = a[i] + a[i + 1];
		int differ = fabs(tar - sum);
		if(differ < min_dif) {
			min_dif = differ;	loc = i;
		}
	}
	// now get a location
	int head(loc), tail(loc + 1);
	vector<pair<int, int>> temp;
	//pair<int, int> nunbers;
	while(head >= 0 && tail < len) {
		//printf("head = %d, tail = %d\n", head, tail);
		sum = a[head] + a[tail];
		if(sum == tar) {
			temp.push_back(pair<int, int>(a[head], a[tail]));
			--head; ++tail;
		}
		else if(sum < tar) { ++tail; }
		else if(sum > tar) { --head; }
	}

	// now get a vector. print them
	for(int i = temp.size() - 1; i >= 0; --i) {
		printf("%d %d\n", temp[i].first, temp[i].second);
	}
	return;
}

int main() {
	int len(0);
	int *list = getArray(len);
	int target(0);
	cin >> target;
	searchPair(list, len, target);
	relase(list, len);
	return 0;
}
