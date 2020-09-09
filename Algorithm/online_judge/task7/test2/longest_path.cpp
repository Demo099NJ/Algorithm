#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;

//#define DEBUG

// all the edges: begin, end and the weight
int info[1000000][3];

struct Edge {
	int neighbor;
	int weight;
	Edge(int n = -1, int w = -1): neighbor(n), weight(w) { ; }
};

const int MAX_VERTICES_NUM = 20000;
const int MAX_NEIGHBOR_NUM = 150;
Edge graph[MAX_VERTICES_NUM][MAX_NEIGHBOR_NUM];
int vertex_num;

int neighbor_num[MAX_VERTICES_NUM];

// for debug
template<class T>
void show_array(T a[], int len) {
	for (int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void get_graph() {
	scanf("%d", &vertex_num);

	int edge_count(0);
	while (EOF != scanf("%d%d%d",\
				&info[edge_count][0], &info[edge_count][1], &info[edge_count][2])) {
		++edge_count;
	}

	// complete the graph
	for (int i = 0; i < edge_count; ++i) {
		int edge_begin = info[i][0];
		graph[edge_begin][neighbor_num[edge_begin]] = Edge(info[i][1], info[i][2]);
		neighbor_num[edge_begin] += 1;
	}

#ifdef DEBUG
	printf("neighbor_num: ");
	show_array(neighbor_num, vertex_num);
#endif
}

void show_graph() {
	for (int i = 0; i < vertex_num; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < neighbor_num[i]; ++j) {
			printf("%d(%d) ", graph[i][j].neighbor, graph[i][j].weight);
		}
		printf("\n");
	}
}

void topological_sort(int topo_order[], int len) {
	int *in_degree = (int *)malloc(sizeof(int) * vertex_num);	assert(in_degree != nullptr);
	// initialize
	for (int i = 0; i < len; ++i) {
		in_degree[i] = 0;
	}

	// fill the in_degree array
	for (int i = 0; i < vertex_num; ++i) {
		for (int j = 0; j < neighbor_num[i]; ++j) {
#ifdef DEBUG
			printf("in_degree[graph[%d][%d].neighbor = %d] = %d\n", \
					i, j, graph[i][j].neighbor, in_degree[graph[i][j].neighbor]);
#endif
			in_degree[graph[i][j].neighbor] += 1;
		}
	}

#ifdef DEBUG
	cout << "array in_degree: ";
	show_array(in_degree, vertex_num);
#endif

	// find the vertex whose in degree is zero
	int stack_pointer(-1);
	for (int i = 0; i < vertex_num; ++i) {
		if (in_degree[i] == 0) {
			in_degree[i] = stack_pointer;
			stack_pointer = i;
		}
	}

#ifdef DEBUG
	cout << "stack_pointer = " << stack_pointer << endl;
#endif
	assert(stack_pointer == 0);

	// topological sort
	int topo_loc(0);
	//for (int i = 0; i < vertex_num; ++i) {
	while (stack_pointer >= 0) {
		topo_order[topo_loc] = stack_pointer;	++topo_loc;
		int previous_top = stack_pointer;
		stack_pointer = in_degree[stack_pointer];
		for (int j = 0; j < neighbor_num[previous_top]; ++j) {
			int temp_neighbor = graph[previous_top][j].neighbor;
			in_degree[temp_neighbor] -= 1;
			if (in_degree[temp_neighbor] == 0) {
				in_degree[temp_neighbor] = stack_pointer;
				stack_pointer = temp_neighbor;
			}
		}
	}

#ifdef DEBUG
	printf("the topological order: ");
	show_array(topo_order, len);
#endif

	free(in_degree);
}

void longest_path(int ver) {
	// get topological order
	int *topo_order = (int *)malloc(sizeof(int) * vertex_num);	assert(topo_order != nullptr);
	topological_sort(topo_order, vertex_num);

	// initialize
	int *path_length = (int *)malloc(sizeof(int) * vertex_num);	assert(path_length != nullptr);
	for (int i = 0; i < vertex_num; ++i) {
		path_length[i] = 0;
	}
	path_length[0] = 0;

	// dp
	int topo_ver(0);
	for (int i = 0; i < vertex_num; ++i) {
		topo_ver = topo_order[i];
		for (int j = 0; j < neighbor_num[topo_ver]; ++j) {
			int temp_neighbor = graph[topo_ver][j].neighbor;
			path_length[temp_neighbor] = max(path_length[temp_neighbor], \
					graph[topo_ver][j].weight + path_length[topo_ver]);
		}
	}

#ifdef DEBUG
	printf("the final result: ");
#endif
	// print the result
	for (int i = 1; i < vertex_num; ++i) {
		printf("%d ", path_length[i]);
	}
	printf("\n");

	free(path_length);
	free(topo_order);
}

int main() {
	// printf("Hello World!\n");
	get_graph();
#ifdef DEBUG
	printf("I got a graph:\n");
	show_graph();
#endif
	longest_path(0);
	return 0;
}
