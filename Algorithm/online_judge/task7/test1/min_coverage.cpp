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

enum State { BLANK, SELECTED, REJECTED };

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
		split_line(line, ' ', e);
		g.push_back(Edge(e[0], nullptr));
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

template<class T>
void show_array(T a[], int len) {
	for (int i = 0; i < len; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int get_min_vertex_coverage(const Graph &tree) {
	int len((int)tree.size());
	State *select_state = new State[len];	assert(select_state != nullptr);
	// initialize
	for (int i = 0; i < len; ++i) {
		select_state[i] = State::BLANK;
	}
	// set the leaves nodes as rejected nodes
	for (int i = 0; i < len; ++i) {
		if (tree[i].next == nullptr) {
			select_state[i] = State::REJECTED;
		}
	}
	// set the nodes whose childs are leaves of this tree as selected nodes
	for (int i = 0; i < len; ++i) {
		Edge *iter = tree[i].next;
		while (iter != nullptr) {
			if (select_state[iter->val] == State::REJECTED) {
				select_state[i] = State::SELECTED;
				break; // useless
			}
			iter = iter->next;
		}
	}
	// traverse all the non leaf nodes to decide the rest nodes' state
	// first of all, get the father of each nodes
	Vertex *parents = new Vertex[len];	assert(parents != nullptr);
	parents[0] = -1;
	for (int i = 0; i < len; ++i) {
		Edge *iter = tree[i].next;
		while (iter != nullptr) {
			parents[iter->val] = i;
			iter = iter->next;
		}
	}
	// traverse all the BLANK nodes
	for (int i = len - 1; i >= 0; --i) {
		if (select_state[i] != State::BLANK) {
			continue;
		}
		// check the state of its parent
		int temp_parent = parents[i];
		if (temp_parent >= 0) {
			// if its parent is selected, it won't be selected
			if (select_state[temp_parent] == State::SELECTED) {
				select_state[i] = State::REJECTED;
				continue;
			}
			// if its parent is rejected, it should be selected
			else if (select_state[temp_parent] == State::REJECTED) {
				select_state[i] = State::SELECTED;
				continue;
			}
		}
		// if one of its childs is selected, it won't be selected
		Edge *iter = tree[i].next;
		select_state[i] = State::SELECTED;
		while (iter != nullptr) {
			if (select_state[iter->val] == State::SELECTED) {
				select_state[i] = State::REJECTED;
				break;
			}
			// if the input is in the preset BFS order, this judgment condition is invalid
			//else if (select_state[iter->val] == State::REJECTED) {
			//	select_state[i] = State::SELECTED;
			//	break;
			//}
			iter = iter->next;
		}
	}
	// the final reault
	int result(0);
	for (int i = 0; i < len; ++i) {
		if (select_state[i] == State::SELECTED) {
			++result;
		}
	}

#ifdef DEBUG
	cout << "parents: ";
	show_array(parents, len);
	cout << "select_state: ";
	show_array(select_state, len);
#endif
	return result;
}

int min_point_coverage(const Graph &tree) {
	int len = (int)tree.size();
	// get the parents of each vertices
	int *parents = new int[len];	assert(parents != nullptr);
	for (int i = 0; i < len; ++i) {
		Edge *iter = tree[i].next;
		while (iter != nullptr) {
			parents[iter->val] = i;
			iter = iter->next;
		}
	}
	parents[0] = -1;
	// store the states of selection
	State *select_state = new State[len];	assert(select_state != nullptr);
	for (int i = 0; i < len; ++i) {
		select_state[i] = State::BLANK;
	}
	// select
	for (int i = 0; i < len; ++i) {
		if (nullptr == tree[i].next) {
			// select all the leaf nodes
			select_state[i] = State::REJECTED;
			int parent_loc = parents[i];
			int present_loc = i;
			// backtracking from leaf nodes
			while (parent_loc != -1) {
				// if the state has been determined, its parents must be determined too
				// according to the rule
				if (State::BLANK != select_state[parent_loc]) {
					break;
				}
				assert(State::BLANK != select_state[present_loc]);
				// select one after the other
				if (State::REJECTED == select_state[present_loc]) {
					select_state[parent_loc] = State::SELECTED;
				}
				else if (State::SELECTED == select_state[present_loc]) {
					select_state[parent_loc] = State::REJECTED;
				}
				// go to next pair
				present_loc = parent_loc;
				parent_loc = parents[parent_loc];
			}
		} 
	}
	// count the number all the selected vertices
	int count(0);
	for (int i = 0; i < len; ++i) {
		if (State::SELECTED == select_state[i]) {
			++count;
		}
	}
#ifdef DEBUG
	cout << "the parents: ";
	show_array(parents, len);
	cout << "the select_state: ";
	show_array(select_state, len);
#endif
	delete[]select_state;
	delete[]parents;
	return count;
}

int traverse_tree(const Graph &tree, int ver, int selected[], int rejected[]) {
	selected[ver] = 1;
	rejected[ver] = 0;
	Edge *iter = tree[ver].next;
	while (iter != nullptr) {
		traverse_tree(tree, iter->val, selected, rejected);
		selected[ver] += min(selected[iter->val], rejected[iter->val]);
		rejected[ver] += selected[iter->val];
		iter = iter->next;
	}
	return 0;
}

int traverse_tree(const Graph &tree, int selected[], int rejected[]) {
	if (0 == (int)tree.size()) {
		return 0;
	}
	traverse_tree(tree, 0, selected, rejected);
	return 1;
}

// dp
int min_coverage(const Graph &tree) {
	int len = (int)tree.size();
	// get the dp array & initialize
	int *dp_selected = new int[len];	assert(dp_selected != nullptr);
	int *dp_rejected = new int[len];	assert(dp_rejected != nullptr);
	for (int i = 0; i < len; ++i) {
		dp_selected[i] = 1;
		dp_rejected[i] = 0;
	}
	// traverse the tree and fill the dp array at the same time
	traverse_tree(tree, dp_selected, dp_rejected);
	// get the final result
	int result(0);
	result = min(dp_selected[0], dp_rejected[0]);
#ifdef DEBUG
	cout << "the dp_selected: ";
	show_array(dp_selected, len);
	cout << "the dp_rejected: ";
	show_array(dp_rejected, len);
#endif
	delete[]dp_rejected;
	delete[]dp_selected;
	return result;
}

int main() {
	Graph tree = get_graph();
#ifdef DEBUG
	show_graph(tree);
	cout << get_min_vertex_coverage(tree) << endl;
	cout << min_point_coverage(tree) << endl;
#endif
	cout << min_coverage(tree) << endl;
	return 0;
}
