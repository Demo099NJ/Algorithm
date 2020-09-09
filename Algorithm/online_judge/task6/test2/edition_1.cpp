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

int dfs(const Graph &g, int len, int ver, Color ver_color[]) {
	int sum(0);
	// color present vertex gray
	ver_color[ver] = Color::GRAY;
	Edge *tmp = g[ver].next;
	while (tmp != nullptr) {
#ifdef DEBUG
		cout << "The color: ";
		for_each(&ver_color[0], &ver_color[len], [](Color c)->void{ cout << c << " "; });
#endif
		if (ver_color[tmp->val] == Color::WHITE) {
#ifdef DEBUG
			printf("recurse %d;\n", ver);
			int temp = dfs(g, len, tmp->val, ver_color);
			printf("the %d returns %d\n", tmp->val, temp);
			sum += 1 + temp;
#else
			sum += 1 + dfs(g, len, tmp->val, ver_color);
#endif
		}
		tmp = tmp->next;
	}
	ver_color[ver] = Color::BLACK;
	return sum;
}

int dfs(const Graph &g, int len, int root) {
	int sum(0);
	Color *ver_color = new Color[len];	assert(ver_color != nullptr);
	// initial
	for_each(&ver_color[0], &ver_color[len], [](Color &c)->void{ c = Color::WHITE; });
	sum = dfs(g, len, root, ver_color);
	delete[]ver_color;
	return sum;
}

int get_max_impact(const Graph &g, vector<Vertex> &vers) {
	// for each vertex, get the impact via DFS
	// preparation
	int len = (int)g.size();
	int max_impact(0), temp_impact(0);
	for (int i = 0; i < len; ++i) {
#ifdef DEBUG
		printf("!!!This is the loop of NO.%d\n", i);
		temp_impact = dfs(g, len, i);
		printf("!!!The end. NO.%d as root returns: %d\n\n", i, temp_impact);
#else
		temp_impact = dfs(g, len, i);
#endif
		if (temp_impact > max_impact) {
			max_impact = temp_impact;
			vers.clear();
			vers.push_back(i);
		}
		else if (temp_impact == max_impact) {
			vers.push_back(i);
		}
	}
	sort(vers.begin(), vers.end(), [](Vertex a, Vertex b)->bool{ return a < b; });
	return max_impact;
}

int main() {
	Graph g = get_graph();
#ifdef DEBUG
	show_graph(g);
#endif
	vector<Vertex> vers;
	cout << get_max_impact(g, vers) << endl;
	for_each(vers.begin(), vers.end(), [](Vertex v)->void{ cout << v << " "; });
#ifdef DEBUG
	cout << endl;
#endif
	return 0;
}
