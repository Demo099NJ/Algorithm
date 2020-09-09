#include<iostream>
#include<assert.h>
using namespace std;
//#define DEBUG

enum Color { WHITE, GREY, BLACK };

struct Vertex {
	int val;
	int weight;
	Vertex *next;
	Vertex(int v = -1, int w = -1, Vertex *n = nullptr) :\
			val(v), weight(w), next(n) { ; }
};

typedef Vertex* Graph;

void add_edge(Graph g, int num, int begin, int end, int weight) {
	Vertex *temp = &g[begin];
	while (temp->next != nullptr) {
		Vertex *node = temp->next;
		if (node->val == end) {
			if (node->weight != weight) {
				exit(-1);
			}
			else {
				return;
			}
		}
		temp = temp->next;
	}
	temp->next = new Vertex(end, weight, nullptr);	assert(temp->next != nullptr);
	return;
}

Graph get_graph(int num) {
	int *weight_edge = new int[num];	assert(weight_edge != nullptr);
	int loc(-1);
	for (int i = 0; i < num; ++i) {
		cin >> loc >> weight_edge[loc - 1];
	}
	Vertex *g = new Vertex[num];	assert(g != nullptr);
	for (int i = 0; i < num; ++i) {
		g[i].weight = weight_edge[i];
	}
	int begin(-1), end(-1);
	while (cin >> end) {
		cin >> begin;
		add_edge(g, num, begin - 1, end - 1, weight_edge[begin - 1]);
	}
	delete[]weight_edge;
	return g;
}

void show_graph(Graph g, int num) {
	Vertex *temp(nullptr);
	for (int i = 0; i < num; ++i) {
		temp = g[i].next;
		printf("%d(%d): ", i, g[i].weight);
		while (temp != nullptr) {
			printf("%d(%d) ", temp->val, temp->weight);
			temp = temp->next;
		}
		cout << endl;
	}
}

void release_graph(Graph g, int num) {
	Vertex *temp(nullptr);
	for (int i = 0; i < num; ++i) {
		temp = g[i].next;
		while (temp != nullptr) {
			Vertex *node = temp;
			temp = temp->next;
			delete node;
		}
	}
	delete[]g;
}

void topo_sort(Graph g, int num, int order[], int ver, int &global, Color ver_color[]) {
	ver_color[ver] = Color::GREY;
	Vertex *temp = g[ver].next;
	while (temp != nullptr) {
		if (ver_color[temp->val] == Color::WHITE) {
			topo_sort(g, num, order, temp->val, global, ver_color);
		}
		temp =  temp->next;
	}
	assert(global >= 0);
	global -= 1;
	order[global] = ver;
	ver_color[ver] = Color::BLACK;
	return;
}

void topo_sort(Graph g, int num, int order[]) {
	int global(num);
	Color *ver_color = new Color[num];	assert(ver_color != nullptr);
	for (int i = 0; i < num; ++i) {
		ver_color[i] = Color::WHITE;
	}
	for (int i = 0; i < num; ++i) {
		if (ver_color[i] == Color::WHITE) {
			topo_sort(g, num, order, i, global, ver_color);
		}
	}
	delete[]ver_color;
	return;
}

int find_the_earliest_start_time(Graph g, int num, int topo_order[]) {
	int *start_time = new int[num];	assert(start_time != nullptr);
	for (int i = 0; i < num; ++i) {
		start_time[i] = 0;
	}
	for (int i = 0; i < num; ++i) {
		int present_ver = topo_order[i];
		Vertex *temp_ver = g[present_ver].next;
		while (temp_ver != nullptr) {
			int temp_weight = start_time[present_ver] + temp_ver->weight;
			int next_ver = temp_ver->val;
			start_time[next_ver] = (start_time[next_ver] > temp_weight) ? start_time[next_ver] : temp_weight;
			temp_ver = temp_ver->next;
		}
	}
	int result(-1); //= start_time[topo_order[num - 1]] + g[topo_order[num - 1]].weight;
	// there may be more than one final task
	for (int i = 0; i < num; ++i) {
		if (g[i].next == nullptr) {
			int temp = start_time[i] + g[i].weight;
			result = temp > result ? temp : result;
		}
	}
	delete[]start_time;
	return result;
}

int get_shortest_time(Graph g, int num) {
	// topology sort first
	// I find that the task scheduling algorithm is another form of BFS
	// the topological order is the queue we use in the BFS
	int *topo_order = new int[num];	assert(topo_order != nullptr);
	for (int i = 0; i < num; ++i) {
		topo_order[i] = -1;
	}
	topo_sort(g, num, topo_order);
#ifdef DEBUG
	cout << "the topological order: ";
	for (int i = 0; i < num; ++i) {
		cout << topo_order[i] << " ";
	}
	cout << endl;
#endif
	int result = find_the_earliest_start_time(g, num, topo_order);
	delete[]topo_order;
	return result;
}

int main() {
	int num(0);
	cin >> num;
	Graph g = get_graph(num);
#ifdef DEBUG
	show_graph(g, num);
#endif
	cout << get_shortest_time(g, num);
	release_graph(g, num);
	return 0;
}
