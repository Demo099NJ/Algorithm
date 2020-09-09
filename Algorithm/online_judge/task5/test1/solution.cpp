#include<iostream>
#include<assert.h>
#include<algorithm>
#include<vector>
using namespace std;
#define DEBUG

typedef pair<int, int> edge;
enum EdgeType { NONEEDGE, GRAPHEDGE, BACKEDGE, TREEEDGE };
enum Color { WHITE, GRAY, BLACK };

EdgeType **get_graph(int &num) {
	cin >> num;
	EdgeType **g = new EdgeType*[num];	assert(g != nullptr);
	for(int i = 0; i < num; ++i) {
		g[i] = new EdgeType[num];	assert(g[i] != nullptr);
		for(int j = 0; j < num; ++j) {
			g[i][j] = EdgeType::NONEEDGE;
		}
	}
	int line(0), column(0);
	while(cin >> line) {
		cin >> column;
		g[line][column] = EdgeType::GRAPHEDGE;
		g[column][line] = EdgeType::GRAPHEDGE;
	}
	//for(int i = 0; i < num; ++i) {
	//	cin >> line >> column;
	//	g[line][column] = EdgeType::GRAPHEDGE;
	//	g[column][line] = EdgeType::GRAPHEDGE;
	//}
	return g;
}

void show_graph(EdgeType **g, int num) {
	if(g == nullptr) {
		return;
	}
	for(int i = 0; i < num; ++i) {
		for(int j = 0; j < num; ++j) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

void release_graph(EdgeType **g, int num) {
	if(g == nullptr) {
		return;
	}
	for(int i = 0; i < num; ++i) {
		if(g[i] == nullptr) {
			continue;
		}
		delete[]g[i];
	}
	delete[]g;
}

int find_cutvertex(EdgeType **graph, int num, Color vertex_color[], int discover_time[],
		int back[], int vertex, int &time, vector<int> &cutvertex) {
	vertex_color[vertex] = Color::GRAY;
	time += 1;
	discover_time[vertex] = time;
	back[vertex] = discover_time[vertex];
	for (int i = 0; i < num; ++i) {
		if (graph[vertex][i] == EdgeType::NONEEDGE) {
			continue;
		}
		//if (vertex_color[i] == Color::GRAY && graph[vertex][i] != EdgeType::TREEEDGE) {
		//	graph[vertex][i] = EdgeType::BACKEDGE;
		//	graph[i][vertex] = EdgeType::BACKEDGE;
		//}
		if (vertex_color[i] == Color::WHITE) {
			graph[vertex][i] = EdgeType::TREEEDGE;
			graph[i][vertex] = EdgeType::TREEEDGE;
			back[i] = find_cutvertex(graph, num, vertex_color, discover_time, \
					back, i, time, cutvertex);
			if (back[i] > discover_time[vertex]) {
				cutvertex.push_back(vertex);
			}
			// exclude root node: in this case, removing this point will not affect
			// the connectivity of the graph, although the root node connects the
			// cycle into the DFS tree
			else if (back[i] == discover_time[vertex] && discover_time[vertex] != 0) {
				cutvertex.push_back(vertex);
			}
			back[vertex] = (back[vertex] < back[i]) ? back[vertex] : back[i];
		}
		else if (vertex_color[i] == Color::GRAY) {
			if (graph[vertex][i] != EdgeType::TREEEDGE) {
				graph[vertex][i] = EdgeType::BACKEDGE;
				graph[i][vertex] = EdgeType::BACKEDGE;
				back[vertex] = (back[vertex] < discover_time[i]) ? back[vertex] : discover_time[i];
			}
		}
		//else if (vertex_color[i] == Color::BLACK) {
		//	back[vertex] = (back[vertex] < back[i]) ? back[vertex] : back[i];
		//}
	}
	time += 1;
	vertex_color[vertex] = Color::BLACK;
	return back[vertex];
}

void find_cutvertex(EdgeType **graph, int num){
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

void find_bridge(EdgeType **graph, int num, Color vertex_color[], int discover_time[], \
		int back[], int vertex, int &time, vector<edge> &bridge) {
	vertex_color[vertex] = Color::GRAY;
	time += 1;
	discover_time[vertex] = time;
	back[vertex] = discover_time[vertex];
	for (int i = 0; i < num; ++i) {
		if (graph[vertex][i] == EdgeType::NONEEDGE) {
			continue;
		}
		if (vertex_color[i] == Color::WHITE) {
			graph[vertex][i] = EdgeType::TREEEDGE;
			graph[i][vertex] = EdgeType::TREEEDGE;
			find_bridge(graph, num, vertex_color, discover_time, back, i, time, bridge);
			back[vertex] = (back[vertex] < back[i]) ? back[vertex] : back[i];
			if (back[i] > discover_time[vertex]) {
				bridge.push_back(edge(vertex, i));
			}
			else if (back[i] == discover_time[vertex] && discover_time[vertex] != 0) {
				bridge.push_back(edge(vertex, i));
			}
			back[vertex] = (back[vertex] < back[i]) ? back[vertex] : back[i];
		}
		else if (vertex_color[i] == Color::GRAY) {
			if (graph[vertex][i] != EdgeType::TREEEDGE) {
				graph[vertex][i] = EdgeType::BACKEDGE;
				graph[i][vertex] = EdgeType::BACKEDGE;
				back[vertex] = (back[vertex] < discover_time[i]) ? back[vertex] : discover_time[i];
			}
		}
	}
	time += 1;
	vertex_color[vertex] = Color::BLACK;
	return;
}

void find_bridge(EdgeType **graph, int num) {
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
	EdgeType **graph = get_graph(num);
	show_graph(graph, num);
	cout << "The cutvertex: " << endl;
	find_cutvertex(graph, num);
	cout << "The bridge: " << endl;
	find_bridge(graph, num);
	release_graph(graph, num);
	return 0;
}
