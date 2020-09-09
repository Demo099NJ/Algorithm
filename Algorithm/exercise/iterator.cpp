#include<iostream>
#include<assert.h>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

const int N = 10;

int main() {
	vector<int> v;
	for (int i = 0; i < N; ++i) {
		v.push_back(i + N);
	}

	for_each(v.begin(), v.end(), [](int a)->void{ cout << a << " "; });
	cout << endl;

	cout << *(v.begin()) << endl;
	cout << &(*(v.begin())) << " " << &(*(v.end())) << endl;

	vector<int>::iterator iter(v.end());
	cout << (*iter) << endl;

	v.push_back(100);
	cout << (*iter) << endl;

	return 0;
}
