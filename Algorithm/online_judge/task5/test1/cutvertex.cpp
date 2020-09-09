#include<iostream>
#include<assert.h>
#include<algorithm>
#include<vector>
using namespace std;
//#define DEBUG

typedef pair<int, int> edge;
enum EdgeType { NONEEDGE, GRAPHEDGE, BACKEDGE, TREEEDGE };
enum Color { WHITE, GRAY, BLACK };

struct Vertex {
	int val;
	EdgeType edge_info;
	Vertex *next;
	Vertex(int v = -1, EdgeType e = EdgeType::NONEEDGE, Vertex *n = nullptr) :\
		val(v), edge_info(e), next(n) { ; }
};

Vertex *get_graph(int &num) {
	cin >> num;
	Vertex *g = new Vertex[num];	assert(g != nullptr);
	int line(-1), column(-1);
	while (cin >> line) {
		cin >> column;
		Vertex *temp = &g[line];
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = new Vertex(column, EdgeType::GRAPHEDGE, nullptr);	assert(temp->next != nullptr);
		temp = &g[column];
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = new Vertex(line, EdgeType::GRAPHEDGE, nullptr);	assert(temp->next != nullptr);
	}
	return g;
}

void show_graph(Vertex *g, int num) {
	if (g == nullptr) {
		return;
	}
	Vertex *temp(nullptr);
	for (int i = 0; i < num; ++i) {
		temp = g[i].next;
		while (temp != nullptr) {
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	return;
}

void release_graph(Vertex *g, int num) {
	if (g == nullptr) {
		return;
	}
	Vertex *temp(nullptr);
	for (int i = 0; i < num; ++i) {
		temp = g[i].next;
		while (temp != nullptr) {
			Vertex *node = temp;
			temp = temp->next;
			delete[]node;
		}
	}
	delete[]g;
}

void set_edge_info(Vertex *graph, int num, int begin, int end, EdgeType type) {
	Vertex *temp = graph[begin].next;
	while (temp != nullptr) {
		if (temp->val == end) {
			temp->edge_info = type;
			break;
		}
		temp = temp->next;
	}
	return;
}

int find_cutvertex(Vertex *graph, int num, Color vertex_color[], int discover_time[],
		int back[], int ver, int &time, vector<int> &cutvertex) {
	vertex_color[ver] = Color::GRAY;
	time += 1;
	discover_time[ver] = time;
	back[ver] = discover_time[ver];
	Vertex *ver_neighbor(graph[ver].next);
	//for (Vertex *ver_neighbor = g[ver].next; ver_neighbor != nullptr; ver_neighbor = ver_neighbor->next)
	while (ver_neighbor != nullptr) {
		//if (graph[ver][i] == EdgeType::NONEEDGE) {
		//	continue;
		//}
		int i = ver_neighbor->val;
		if (vertex_color[i] == Color::WHITE) {
			ver_neighbor->edge_info = EdgeType::TREEEDGE;	// set edge ver-i as type tree edge;
			set_edge_info(graph, num, i, ver, EdgeType::TREEEDGE);
			back[i] = find_cutvertex(graph, num, vertex_color, discover_time, \
					back, i, time, cutvertex);
			if (back[i] > discover_time[ver]) {
				cutvertex.push_back(ver);
			}
			// exclude root node: in this case, removing this point will not affect
			// the connectivity of the graph, although the root node connects the
			// cycle into the DFS tree
			else if (back[i] == discover_time[ver] && discover_time[ver] != 0) {
				cutvertex.push_back(ver);
			}
			back[ver] = (back[ver] < back[i]) ? back[ver] : back[i];
		}
		else if (vertex_color[i] == Color::GRAY) {
			if (ver_neighbor->edge_info != EdgeType::TREEEDGE) {
				ver_neighbor->edge_info = EdgeType::BACKEDGE;
				set_edge_info(graph, num, i, ver, EdgeType::BACKEDGE);
				back[ver] = (back[ver] < discover_time[i]) ? back[ver] : discover_time[i];
			}
		}
		ver_neighbor = ver_neighbor->next;
	}
	time += 1;
	vertex_color[ver] = Color::BLACK;
	return back[ver];
}

void find_cutvertex(Vertex *graph, int num){
	Color *vertex_color = new Color[num];	assert(vertex_color != nullptr);
	int *discover_time = new int[num];	assert(discover_time != nullptr);
	int *back = new int[num];	assert(back != nullptr);
	for (int i = 0; i < num; ++i) {
		vertex_color[i] = Color::WHITE;
		discover_time[i] = -1;
		back[i] = -1;
	}
	int time(-1);
	vector<int> cutvertex;
	for (int i = 0; i < num; ++i) {
		if (vertex_color[i] == Color::WHITE) {
			find_cutvertex(graph, num, vertex_color, discover_time, back, i, time, cutvertex);
		}
	}
#ifdef DEBUG
	cout << "the back: ";
	for (int i = 0; i < num; ++i) {
		cout << back[i] << " ";
	}
	cout << endl;
	cout << "the discover time: ";
	for (int i = 0; i < num; ++i) {
		cout << discover_time[i] << " ";
	}
	cout << endl;
#endif
	// format & output
	sort(cutvertex.begin(), cutvertex.end());
	for (int i = 0; i < (int)cutvertex.size(); ++i) {
		cout << cutvertex[i] << endl;
	}
	//cout << endl;
	delete[]vertex_color;
	delete[]discover_time;
	delete[]back;
	return;
}

void find_bridge(Vertex *graph, int num, Color vertex_color[], int discover_time[], \
		int back[], int ver, int &time, vector<edge> &bridge) {
	vertex_color[ver] = Color::GRAY;
	time += 1;
	discover_time[ver] = time;
	back[ver] = discover_time[ver];
	Vertex *ver_neighbor(graph[ver].next);
	//for (Vertex *ver_neighbor = g[ver].next; ver_neighbor != nullptr; ver_neighbor = ver_neighbor->next)
	while (ver_neighbor != nullptr) {
		int i = ver_neighbor->val;
		if (vertex_color[i] == Color::WHITE) {
			ver_neighbor->edge_info = EdgeType::TREEEDGE;
			set_edge_info(graph, num, i, ver, EdgeType::TREEEDGE);
			find_bridge(graph, num, vertex_color, discover_time, back, i, time, bridge);
			back[ver] = (back[ver] < back[i]) ? back[ver] : back[i];
			if (back[i] > discover_time[ver]) {
				bridge.push_back(edge(ver, i));
			}
			else if (back[i] == discover_time[ver] && discover_time[ver] != 0) {
				bridge.push_back(edge(ver, i));
			}
			back[ver] = (back[ver] < back[i]) ? back[ver] : back[i];
		}
		else if (vertex_color[i] == Color::GRAY) {
			if (ver_neighbor->edge_info != EdgeType::TREEEDGE) {
				ver_neighbor->edge_info = EdgeType::BACKEDGE;
				set_edge_info(graph, num, i, ver, EdgeType::BACKEDGE);
				back[ver] = (back[ver] < discover_time[i]) ? back[ver] : discover_time[i];
			}
		}
		ver_neighbor = ver_neighbor->next;
	}
	time += 1;
	vertex_color[ver] = Color::BLACK;
	return;
}

void find_bridge(Vertex *graph, int num) {
	Color *vertex_color = new Color[num];	assert(vertex_color != nullptr);
	int *discover_time = new int[num];	assert(discover_time != nullptr);
	int *back = new int[num];	assert(back != nullptr);
	for (int i = 0; i < num; ++i) {
		vertex_color[i] = Color::WHITE;
		discover_time[i] = -1;
		back[i] = -1;
	}
	int time(-1);
	vector<edge> bridge;
	for (int i = 0; i < num; ++i) {
		if (vertex_color[i] == Color::WHITE) {
			find_bridge(graph, num, vertex_color, discover_time, back, i, time, bridge);
		}
	}
	// format & output
	for (int i = 0; i < (int)bridge.size(); ++i) {
		if (bridge[i].first > bridge[i].second) {
			swap(bridge[i].first, bridge[i].second);
		}
	}
	sort(bridge.begin(), bridge.end(), [](edge a, edge b)->bool{ return a.first < b.first; });
	for (int i = 0; i < (int)bridge.size(); ++i) {
		cout << bridge[i].first << " " << bridge[i].second << endl;
	}
	delete[]vertex_color;
	delete[]discover_time;
	delete[]back;
	return;
}

int main() {
	int num(0);
	Vertex *graph = get_graph(num);
	//show_graph(graph, num);
	//cout << "The cutvertex: " << endl;
	find_cutvertex(graph, num);
	//cout << "The bridge: " << endl;
	find_bridge(graph, num);
	release_graph(graph, num);
	return 0;
}
