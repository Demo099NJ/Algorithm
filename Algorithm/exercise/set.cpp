#include<iostream>
#include<assert.h>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int main() {
	set<int> s1;
	for (int i = 0; i < 10; ++i) {
		s1.insert(i);
	}
	for_each(s1.begin(), s1.end(), [](int tmp)->void{ cout << tmp << " "; });
	cout << endl;
	cout << s1.insert(7).second << endl;

	vector<int> v;
	for (int i = 0; i < 10; ++i) {
		v.push_back(i);
	}
	set<int> s2(v.begin(), v.end());
	for_each(s2.begin(), s2.end(), [](int tmp)->void{ cout << tmp << " "; });
	cout << endl;

	return 0;
}
