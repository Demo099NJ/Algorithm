#include<iostream>
#include<assert.h>
#include<vector>
#include<set>
#include<string>
#include<algorithm>
using namespace std;

// the core idea is BFS

//#define DEBUG

typedef int Vertex;
struct Edge {
	Vertex val;
	Edge *next;
	Edge(Vertex v = -1, Edge *n = nullptr): val(v), next(n) { ; }
};
typedef vector<Edge> Graph;

enum Color { WHITE, GRAY, BLACK };

bool move_tail(string &str, char ch) {
	if (ch == *(str.end())) {
		str.pop_back();
		return true;
	}
	return false;
}

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
}

bool add_edge(Graph &g, int v, vector<Vertex> e) {
	Edge *iter = &g[v];
	while (iter->next != nullptr) {
		iter = iter->next;
	}
	for (int i = 1; i < (int)e.size(); ++i){
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
		move_tail(line, '\n');
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

void insert_neighbor(const Graph &g, Vertex v, Color ver_color[], vector<Vertex> &one) {
	Edge *tmp = g[v].next;
	while (tmp != nullptr) {
		if (Color::WHITE == ver_color[tmp->val]) {
			one.push_back(tmp->val);
			ver_color[tmp->val] = Color::BLACK;
		}
		tmp = tmp->next;
	}
}

void get_one_side(const Graph &g, Vertex start, vector<Vertex> &side) {
	// preparation
	vector<Vertex> another_side;
	int len = (int)g.size();
	Color *ver_color = new Color[len];	assert(ver_color != nullptr);
	for_each(&ver_color[0], &ver_color[len], [](Color &a)->void{ a = Color::WHITE; });
#ifdef DEBUG
	for_each(&ver_color[0], &ver_color[len], [](Color &a)->void{ cout << a << " "; });
	cout << endl;
	int counter = 0;
#endif
	// initialize
	side.push_back(start);
	ver_color[start] = Color::BLACK;
	// begin working
	int i(0), j(0);
	while ((side.size() + another_side.size()) < g.size()) {
		for (; i < (int)side.size(); ++i) {
			insert_neighbor(g, side[i], ver_color, another_side);
		}
		for (; j < (int)another_side.size(); ++j) {
			insert_neighbor(g, another_side[j], ver_color, side);
		}
#ifdef DEBUG
		++counter;
		assert(counter < 10);
		cout << "in the beginning: " << i << " " << j << " ";
		cout << "size: " << side.size() << " and " << another_side.size() << ";";
		cout << "side: ";
		for_each(side.begin(), side.end(), [](Vertex v)->void{ cout << v << " "; });
		cout << "another_side: ";
		for_each(another_side.begin(), another_side.end(), [](Vertex v)->void{ cout << v << " "; });
		cout << "the color: ";
		for_each(&ver_color[0], &ver_color[len], [](Color &a)->void{ cout << a << " "; });
		cout << endl;
#endif
	}
	sort(side.begin(), side.end(), [](int a, int b)->bool{ return a < b; });
	delete[]ver_color;
	return;
}

int main() {
	Graph g = get_graph();
#ifdef DEBUG
	show_graph(g);
#endif
	vector<Vertex> vers;
	get_one_side(g, 0, vers);
	for_each(vers.begin(), vers.end(), [](Vertex v)->void{ cout << v << endl; });
	return 0;
}
