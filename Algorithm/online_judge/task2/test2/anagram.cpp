#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

struct node {
	string val;
	int num;
	node(string v = "", int n = 0): val(v), num(n) { ; }
};

string *getArray(int len) {
	string *array = new string[len];	assert(array != nullptr);
	for(int i = 0; i < len; ++i) {
		cin >> array[i];
	}
	return array;
}

void swap(string &a, string &b) {
	string temp = a;
	a = b;
	b = temp;
}

// use quick sort
void quickSort(vector<string> &a, int first, int last) {
	//cout << "emmmm" << endl;
	if(first < last) {
		string pivot = a[last];
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

		quickSort(a, first, temp - 1);
		quickSort(a, temp + 1, last);
	}
	return;
}

void quickSort(vector<string> &a) {
	quickSort(a, 0, a.size() - 1);
	return;
}

// if string a and b are qualified, return true; or, return false;
bool is_anagram(string a, string b) {
	if(a.size() != b.size()) { return false; }
	// suppose the letters in the test case are all lowercase
	int valA[26] = { 0 }, valB[26] = { 0 };
	for(int i = 0; i < (int)a.size(); ++i) {
		valA[a[i] - 'a'] += 1;	
	}
	for(int i = 0; i < (int)b.size(); ++i) {
		valB[b[i] - 'a'] += 1;
	}
	for(int i = 0; i < 26; ++i) {
		if(valA[i] != valB[i]) { return false; }
	}
	return true;
}

// use equivalence class to solve this problem
// but I only need the root of each set
void selectAnagram(vector<string> &ret, string a[], int len) {
	vector<node> strSet;
	node temp(a[0], 1);
	strSet.push_back(temp);
	bool is_new_set(true);
	for(int i = 1; i < len; ++i) {
		is_new_set = true;
		for(int j = 0; j < (int)strSet.size(); ++j) {
			// if belongs to one of the sets
			if(is_anagram(a[i], strSet[j].val)) {
				// get the less string in dictionary order
				if(a[i] < strSet[j].val) {
					strSet[j].val = a[i];
				}
				// sum of the set increase
				strSet[j].num += 1;
				is_new_set = false;
				break;
			}
		}
		// this string doesn't belong to any sets
		if(is_new_set) {
			temp.val = a[i];
			temp.num = 1;
			strSet.push_back(temp);
		}
	}

	// get the real anagram, whose set own more than 1 string
	for(int i = 0; i < (int)strSet.size(); ++i) {
		if(strSet[i].num > 1) {
			ret.push_back(strSet[i].val);
		}
	}

	//cout << "for debugging: " << endl;
	//for(int i = 0; i < (int)strSet.size(); ++i) {
	//	cout << strSet[i].val << " " << strSet[i].num << endl;
	//}
	return;
}

void showArray(string a[], int len) {
	for(int i = 0; i < len; ++i) {
		cout << a[i] << endl;
	}
	return;
}

int main() {
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	int len(0);
	cin >> len;
	string *strArray = getArray(len);
	vector<string> result;
	selectAnagram(result, strArray, len);
	quickSort(result);
	// output the numbers
	cout << result.size() << endl;
	// output the results
	for(int i = 0; i < (int)result.size(); ++i) {
		cout << result[i] << endl;
	}
	return 0;
}
