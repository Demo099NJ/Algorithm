#include<iostream>
#include<assert.h>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//#define DEBUG

typedef int Vertex;
struct Edge {
	Vertex val;
	Edge *next;
	Edge(Vertex v = -1, Edge *n = nullptr): val(v), next(n) { ; }
};
typedef vector<Edge> Graph;

enum Color { WHITE, GRAY, BLACK };

void split_line(string &str, char ch, vector<Vertex> &e) {
	int num(0);
	for (int i = 0; i < (int)str.size(); ++i) {
		if (str[i] == ' ' || str[i] == '\n') {
			e.push_back(num);
			num = 0;
		}
		else {
			num = num * 10 + (int)(str[i] - '0');
		}
	}
	e.push_back(num);
}

bool add_edge(Graph &g, int v, Vertex e) {
	Edge *iter = &g[v];
	while (iter->next != nullptr) {
		iter = iter->next;
	}
	iter->next = new Edge(e, nullptr);	assert(iter->next != nullptr);
	return true;
}

bool add_edge(Graph &g, int v, vector<Vertex> e) {
	Edge *iter = &g[v];
	while (iter->next != nullptr) {
		iter = iter->next;
	}
	for (int i = 0; i < (int)e.size(); ++i){
		iter->next = new Edge(e[i], nullptr);	assert(iter->next != nullptr);
		iter = iter->next;
	}
	return true;
}

Graph get_graph() {
	Graph g;
	string line;
	vector<Vertex> e;
	for (int i = 0; getline(cin, line); ++i) {
#ifdef DEBUG
		cout << "I got a line(size = " << line.size() << "): " << line << endl;
#endif
		split_line(line, ' ', e);
		g.push_back(Edge(i, nullptr));
		add_edge(g, i, e);
		e.clear();
	}
	return g;
}

void show_graph(const Graph &g) {
	for (int i = 0; i < (int)g.size(); ++i) {
		cout << i << ": ";
		Edge *iter = g[i].next;
		while (iter != nullptr) {
			cout << iter->val << " ";
			iter = iter->next;
		}
		cout << endl;
	}
	return;
}

void transpose(const Graph &g, Graph &transpose_graph, int len) {
	vector<vector<Vertex>> edges(len);
	for (int i = 0; i < len; ++i) {
		Edge *iter = g[i].next;
		while (iter != nullptr) {
			edges[iter->val].push_back(i);
			iter = iter->next;
		}
	}
	for (int i = 0; i < len; ++i) {
		transpose_graph.push_back(Edge(i, nullptr));
	}
	//
	for (int i = 0; i < len; ++i) {
		add_edge(transpose_graph, i, edges[i]);
	}
	return;
}

void dfs_base(const Graph &g, int len, int ver, Color ver_color[], vector<Vertex> &visit_ver) {
	ver_color[ver] = Color::GRAY;
	Edge *iter = g[ver].next;
	while (iter != nullptr) {
		if (ver_color[iter->val] == Color::WHITE) {
			dfs_base(g, len, iter->val, ver_color, visit_ver);
		}
		iter = iter->next;
	}
	ver_color[ver] = Color::BLACK;
	visit_ver.push_back(ver);
	return;
}

void dfs_get_order(const Graph &g, int len, int root, vector<Vertex> &visit_ver) {
	// preparation
#ifdef DEBUG
	cout << "DFS" << endl;
#endif
	Color *ver_color = new Color[len];	assert(ver_color != nullptr);
	for (int i = 0; i < len; ++i) {
		ver_color[i] = Color::WHITE;
	}
	for (int i = 0; i < len; ++i) {
		if (ver_color[i] == Color::WHITE) {
			dfs_base(g, len, i, ver_color, visit_ver);
		}
	}
	delete[]ver_color;
	return;
}

void dfs_get_scc(const Graph &g, int len, int root, \
		const vector<Vertex> &visit_ver, vector<vector<Vertex>> &scc) {
	// preparation
#ifdef DEBUG
	;
#endif
	vector<Vertex> temp;
	Color *ver_color = new Color[len];	assert(ver_color != nullptr);
	for (int i = 0; i < len; ++i) {
		ver_color[i] = Color::WHITE;
	}
	for (int i = 0; i < len; ++i) {
		int loc = visit_ver[len - i - 1];
		if (ver_color[loc] == Color::WHITE) {
			dfs_base(g, len, loc, ver_color, temp);
			scc.push_back(temp);
			temp.clear();
		}
	}
	delete[]ver_color;
	return;
}

int find_scc(Vertex ver, const vector<vector<Vertex>> &scc) {
	for (int i = 0; i < (int)scc.size(); ++i) {
		for (int j = 0; j < (int)scc[i].size(); ++j) {
			if (ver == scc[i][j]) {
				return i;
			}
		}
	}
	return -1;
}

void construct_compressed_tree(const Graph &g, const vector<vector<Vertex>> &scc, \
		Graph &c_tree, vector<int> &weight) {
	for (int i = 0; i < (int)scc.size(); ++i) {
		c_tree.push_back(Edge(i, nullptr));
		weight.push_back((int)scc[i].size());
	}
	int len = (int)g.size();
	Vertex *set_nodes = new Vertex[len];	assert(set_nodes != nullptr);
	for (int i = 0; i < len; ++i) {
		set_nodes[i] = -1;
	}
	for (int i = 0; i < (int)scc.size(); ++i) {
		for (int j = 0; j < (int)scc[i].size(); ++j) {
			int loc = scc[i][j];
			set_nodes[loc] = i;
		}
	}
	// construct a compressed tree
	vector<vector<Vertex>> temp_edges((int)c_tree.size());
	for (int i = 0; i < (int)g.size(); ++i) {
		Edge *tmp = g[i].next;
		while (tmp != nullptr) {
			int loc = tmp->val;
			if (set_nodes[loc] != set_nodes[i]) {
				temp_edges[set_nodes[i]].push_back(set_nodes[loc]);
			}
			tmp = tmp->next;
		}
	}
	for (int i = 0; i < (int)temp_edges.size(); ++i) {
		add_edge(c_tree, i, temp_edges[i]);
	}
	delete[]set_nodes;
	return;
}

int max_node_num(const Graph &c_tree, Vertex root, \
		const vector<int> &weight, int total_weight[]) {
	if (total_weight[root] >= 0) {
		return root;
	}
	Edge *tmp = c_tree[root].next;
	int temp_loc(-1), max_weight(weight[root]);
	while (tmp != nullptr) {
		temp_loc = max_node_num(c_tree, tmp->val, weight, total_weight);
		max_weight += total_weight[temp_loc];
		tmp = tmp->next;
	}
	total_weight[root] = max_weight;
	return root;
}

int max_node_num(const Graph &c_tree, const vector<int> &weight, int &max) {
	int len = (int)c_tree.size();
	int *total_weight = new int[len];	assert(total_weight != nullptr);
	for (int i = 0; i < len; ++i) {
		total_weight[i] = -1;
	}
	int result(-1);//,  max_weight(0);
	for (int i = 0; i < len; ++i) {
		if (total_weight[i] < 0) {
			max_node_num(c_tree, i, weight, total_weight);
		}
	}
	int temp_max(-1);//, temp_result(1);
	for (int i = 0; i < len; ++i) {
		if (temp_max < total_weight[i]) {
			temp_max = total_weight[i];
			result = i;
		}
	}
	max = temp_max - 1;
#ifdef DEBUG
	cout << "the weight: ";
	for_each(weight.begin(), weight.end(), [](int i)->void{ cout << i << " "; });
	cout << endl;
	cout << "total_weight: ";
	for (int i = 0; i < len; ++i) {
		cout << total_weight[i] << " ";
	}
	cout << endl;
#endif
	delete[]total_weight;
	return result;
}

int get_max_impact(const Graph &g, vector<Vertex> &vers) {
	int len = (int)g.size();
	vector<Vertex> visit_ver;
	dfs_get_order(g, len, 0, visit_ver);
	Graph transpose_graph;
	transpose(g, transpose_graph, len);
#ifdef DEBUG
	printf("(int)visit_ver.size() = %d\n", (int)visit_ver.size());
#endif
	vector<vector<Vertex>> scc;
	int scc_num = (int)visit_ver.size();	assert(scc_num - 1 >= 0);
	dfs_get_scc(transpose_graph, len, visit_ver[scc_num - 1], visit_ver, scc);
#ifdef DEBUG
	cout << "I got the scc:" << endl;
	for (int i = 0; i < (int)scc.size(); ++i) {
		for (int j = 0; j < (int)scc[i].size(); ++j) {
			cout << scc[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl;
#endif
	Graph c_tree;
	vector<int> weight;
	construct_compressed_tree(g, scc, c_tree, weight);
#ifdef DEBUG
	cout << "I got the compressed tree: " << endl;
	show_graph(c_tree);
#endif
	int max_weight = -1;
	int result = max_node_num(c_tree, weight, max_weight);
	vers = scc[result];
	sort(vers.begin(), vers.end());
	return max_weight;
}

int main() {
	Graph g = get_graph();
#ifdef DEBUG
	cout << "I got a graph: " << endl;
	show_graph(g);
	Graph t_g;
	transpose(g, t_g, (int)g.size());
	cout << "I got a transpose: " << endl;
	show_graph(t_g);
#endif
	vector<Vertex> vers;
	cout << get_max_impact(g, vers) << endl;
	for_each(vers.begin(), vers.end(), [](Vertex v)->void{ cout << v << " "; });
	cout << endl;
	return 0;
}
