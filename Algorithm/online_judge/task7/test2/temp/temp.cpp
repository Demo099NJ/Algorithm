#include<iostream>
#include<assert.h>
using namespace std;

struct node {
    int begin;
    int end;
    int weight;
};
node tmp[1000000];

struct Vertex {
    int end;
    int weight;
    Vertex(int e = -1, int w = 0): end(e), weight(w) { ; }
};
Vertex graph[20000][100];
int length[20000];


int main() {
    int len = 0;
    scanf("%d", &len);

    // assert(len <= 20000);

    //for (int i = 0; i < 100; ++i)  {
    //    printf("%d: %d(%d)", 0, graph[0][i].end, graph[0][i].weight);
    //}

    int begin(0), end(0), weight(0);
    int count(0);
    while (scanf("%d%d%d", &begin, &end, &weight) != EOF) {
        tmp[count].begin = begin;
        tmp[count].end = end;
        tmp[count].weight = weight;
        ++count;
    }

    for (int i = 0; i < count; ++i) {
        int temp_begin = tmp[i].begin;
        graph[temp_begin][length[temp_begin]].end = tmp[i].end;
        graph[temp_begin][length[temp_begin]].weight = tmp[i].weight;
        ++length[temp_begin];
    }

    // assert(count <= 500000);

    printf("%d", len);
    
    return 0;
}
