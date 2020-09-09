#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;

//#define DEBUG

struct Block {
    int begin;
    int end;
    int weight;
	Block(int b = -1, int e = -1, int w = 0): begin(b), end(e), weight(w) { ; }
};
Block tmp[1000000];

typedef int Vertex;
struct Edge {
    Vertex end;
    int weight;
    Edge(int e = -1, int w = 0): end(e), weight(w) { ; }
};
Edge graph[20000][100];
int num;

int length[20000];

enum Color { WHITE, GRAY, BLACK };

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

void get_graph() {
	// get the total number of vertices
	scanf("%d", &num);

	// get data
	int begin(-1), end(-1), weight(-1);
	int count(0);
	while (EOF != scanf("%d%d%d", &begin, &end, &weight)) {
		//add_edge(begin, end, weight);
		tmp[count] = Block(begin, end, weight);
		++count;
	}

#ifdef DEBUG
	cout << "in the beginning, the length: ";
	show_array(length, num);

	// useless
	// be prepared for the worst
	for (int i = 0; i < num; ++i) {
		length[i] = 0;
	}
#endif

	// complete the graph
	for (int i = 0; i < count; ++i) {
		int temp_begin = tmp[i].begin;
		assert(temp_begin < num);
		graph[temp_begin][length[temp_begin]] = Edge(tmp[i].end, tmp[i].weight);
		length[temp_begin] += 1;
	}

#ifdef DEBUG
	cout << "the length: ";
	show_array(length, num);
#endif

	return;
}

void show_graph() {
	for (int i = 0; i < num; ++i) {
		cout << i << ": ";
		for (int j = 0; j < length[i]; ++j) {
			printf("%d(%d) ", graph[i][j].end, graph[i][j].weight);
		}
		cout << endl;
	}
	return;
}

void topo_sort(int order[], int ver, int &global, Color ver_color[]) {
	ver_color[ver] = Color::GRAY;
	int temp_len = length[ver];
	for (int i = 0; i < temp_len; ++i) {
		int neighbor = graph[ver][i].end;
		if (ver_color[neighbor] == Color::WHITE) {
			topo_sort(order, neighbor, global, ver_color);
		}
	}
	assert(global >= 0);
	global -= 1;
	order[global] = ver;
	ver_color[ver] = Color::BLACK;
	return;
}

void topo_sort(int order[]) {
	int global(num);
	Color *ver_color = (Color *)malloc(sizeof(Color) * num);	assert(ver_color != nullptr);

	// initilize
	for (int i = 0; i < num; ++i) {
		ver_color[i] = Color::WHITE;
	}

	// go through
	for (int i = 0; i < num; ++i) {
		if (ver_color[i] == Color::WHITE) {
			topo_sort(order, i, global, ver_color);
		}
	}

	free(ver_color);
	return;
}

int topological_sort(int topo_order[]) {
	int *in_degree = (int *)malloc(sizeof(int) * num);	assert(in_degree != nullptr);
	// initilize as 0
	for (int i = 0; i < num; ++i) {
		in_degree[i] = 0;
	}

	// fill in degree of all the vertices
	for (int i = 0; i < num; ++i) {
		int temp_len = length[i];
		for (int j = 0; j < temp_len; ++j) {
			in_degree[graph[i][j].end] += 1;
		}
	}

#ifdef DEBUG
	cout << "in the beginning, in_degree: ";
	show_array(in_degree, num);
#endif

	// find the point whose degree is 0
	int loc(-1);
	for (int i = 0; i < num; ++i) {
		if (0 == in_degree[i]) {
			in_degree[i] = loc;
			loc = i;
		}
	}
	//assert(0 == loc);

#ifdef DEBUG
	cout << "after initilize, in_degree: ";
	show_array(in_degree, num);
	cout << "loc = " << loc << endl;
#endif

	int pointer(0);
	// get the topological order
	while (loc >= 0) {
		// fill topo_order
		topo_order[pointer] = loc;	++pointer;
		int primary_loc = loc;
		// get next loc
		loc = in_degree[loc];
		// go through its neightbors
		int temp_len = length[primary_loc];
		for (int j = 0; j < temp_len; ++j) {
			int neightbor = graph[primary_loc][j].end;
			in_degree[neightbor] -= 1;
			if (0 == in_degree[neightbor]) {
				in_degree[neightbor] = loc;
				loc = neightbor;
			}
		}
	}

	free(in_degree);
	return 0;
}

// dp problem
int longest_path(int ver) {
	// topological sort
	int *topo_order = (int *)malloc(sizeof(int) * num);	assert(nullptr != topo_order);
	topological_sort(topo_order);
	//topo_sort(topo_order);
	//assert(0 == topo_order[0]);

	// count the path
	int *path_length = (int *)malloc(sizeof(int) * num);	assert(nullptr != path_length);
	for (int i = 0; i < num; ++i) {
		path_length[i] = 0;
	}

	// work
	for (int i = 0; i < num; ++i) {
		int loc = topo_order[i];
		int temp_len = length[loc];
		for (int j = 0; j < temp_len; ++j) {
			int neightbor = graph[loc][j].end;
			path_length[neightbor] = \
				max(path_length[neightbor], graph[loc][j].weight + path_length[loc]);
		}
	}

	// print final result
	for (int i = 1; i < num; ++i) {
		printf("%d ", path_length[i]);
	}
	printf("\n");
	
#ifdef DEBUG
	cout << "the topological order: ";
	show_array(topo_order, num);
	cout << "the total weight: " << path_length[ver] << endl;
#endif

	free(path_length);
	free(topo_order);
	return 0;
}

int main() {
	get_graph();
#ifdef DEBUG
	cout << "Hello World!" << endl;
	show_graph();
#endif
	longest_path(0);
	return 0;
}
