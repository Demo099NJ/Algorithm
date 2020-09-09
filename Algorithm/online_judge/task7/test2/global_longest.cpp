#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
using namespace std;

#define DEBUG

typedef int Vertex;
struct Edge {
	Vertex val;
	int weight;
	Edge *next;
	Edge(Vertex v = -1, int w = -1, Edge *n = nullptr): val(v), weight(w), next(n) { ; }
};
typedef Edge* Graph;

enum Color { WHITE, GRAY, BLACK };

bool add_edge(Graph g, Vertex begin, Vertex end, int weight, Edge *pointers[]) {
	Edge *iter = pointers[begin];
	while (iter->next != nullptr) {
		iter = iter->next;
	}
	iter->next = new Edge(end, weight, nullptr);	assert(iter->next != nullptr);
	pointers[begin] = iter->next;
	return true;
}

Graph get_graph(int &len) {
	cin >> len;
	Graph g = new Edge[len];	assert(nullptr != g);
	for (int i = 0; i < len; ++i) {
		g[i].val = i;
	}
	// for faster speed at the expense of space
	Edge **pointers = new Edge*[len];	assert(nullptr != pointers);
	for (int i = 0; i < len; ++i) {
		pointers[i] = &g[i];
	}
	// get data
	int begin(-1), end(-1), weight(-1);
	while (cin >> begin) {
		cin >> end >> weight;
		add_edge(g, begin, end, weight, pointers);
	}
	return g;
}

void show_graph(Graph g, int len) {
	for (int i = 0; i < len; ++i) {
		cout << i << ": ";
		Edge *iter = g[i].next;
		while (iter != nullptr) {
			cout << iter->val << "(" << iter->weight << ") ";
			iter = iter->next;
		}
		cout << endl;
	}
	return;
}

void release_graph(Graph g, int num) {
	if (nullptr == g) {
		return;
	}
	for (int i = 0; i < num; ++i) {
		Edge *iter = g[i].next;
		while (nullptr != iter) {
			Edge *temp = iter;
			iter = iter->next;
			delete temp;
		}
	}
	delete[]g;
}

template<class T>
void show_array(T a[], int len) {
	if (a == nullptr) {
		return;
	}
	for (int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int topological_sort(Graph g, int num, int topo_order[]) {
	int *in_degree = new int[num];	assert(in_degree != nullptr);
	// initilize as 0
	for (int i = 0; i < num; ++i) {
		in_degree[i] = 0;
	}
	// fill the in degree
	for (int i = 0; i < num; ++i) {
		Edge *iter = g[i].next;
		while (nullptr != iter) {
			in_degree[iter->val] += 1;
			iter = iter->next;
		}
	}
	// find the point whose degree is 0
	int loc(-1);
	for (int i = 0; i < num; ++i) {
		if (0 == in_degree[i]) {
			in_degree[i] = loc;
			loc = i;
		}
	}
	int pointer(0);
	// get the topological order
	while (loc >= 0) {
		// fill topo_order
		topo_order[pointer] = loc;	++pointer;
		Edge *iter = g[loc].next;
		// get next loc
		loc = in_degree[loc];
		while (nullptr != iter) {
			in_degree[iter->val] -= 1;
			if (0 == in_degree[iter->val]) {
				in_degree[iter->val] = loc;
				loc = iter->val;
			}
			iter = iter->next;
		}
	}
	return 0;
}

// dp problem
int longest_path(Graph g, int num, int ver) {
	// topological sort
	int *topo_order = new int[num];	assert(topo_order != nullptr);
	topological_sort(g, num, topo_order);
	// count the path
	int *path_length = new int[num];	assert(nullptr != path_length);
	for (int i = 0; i < num; ++i) {
		path_length[i] = 0;
	}
	// work
	for (int i = num - 1; i >= 0; --i) {
		int loc = topo_order[i];
		Edge *iter = g[loc].next;
		while (nullptr != iter) {
			path_length[loc] = max(path_length[loc], iter->weight + path_length[iter->val]);
			iter = iter->next;
		}
	}
#ifdef DEBUG
	cout << "the topological order: ";
	show_array(topo_order, num);
	cout << "the path length:";
	show_array(path_length, num);
	cout << "the total weight: " << path_length[ver] << endl;
#endif
	int result = path_length[ver];
	delete[]path_length;
	delete[]topo_order;
	return result;
}

int main() {
	int num(0);
	Graph g = get_graph(num);
#ifdef DEBUG
	cout << "Hello World!" << endl;
	show_graph(g, num);
#endif
	longest_path(g, num, 0);
	release_graph(g, num);
	return 0;
}
