#include<iostream>
#include<assert.h>
using namespace std;

//#define TEST
#define SILLY

int main() {
	int len = 0;
	scanf("%d", &len);
	
#ifdef TEST
	int begin = 0, end = 0, weight = 0;
	while (scanf("%d%d%d", &begin, &end, &weight) != EOF);

	for (int i = 1; i < len; ++i) {
		printf("%d ", i * i);
	}
	printf("\n");

	return 0;

#else

#ifdef SILLY
	int **g = (int **)malloc(sizeof(int *) * len);	assert(g != NULL);
	for (int i = 0; i < len; ++i) {
		g[i] = (int *)malloc(sizeof(int) * len);	assert(g[i] != NULL);
		//for (int j = 0; j < len; ++j) {
		//	g[i][j] = 0;
		//}
	}
	//cout << "Hello" << endl;
#else
	int g[1000][1000];
	//cout << "World" << endl;
#endif

	int begin = 0, end = 0, weight = 0;
	while (scanf("%d%d%d", &begin, &end, &weight) != EOF) {
		g[begin][end] = weight;
	}

	int *path = (int *)malloc(sizeof(int) * len);	assert(path != NULL);
	for (int i = 0; i < len; ++i) {
		path[i] = g[0][i];
	}

	for (int i = 1; i < len; ++i) {
		printf("%d ", path[i]);
	}
	printf("\n");

#ifdef SILLY
	for (int i = 0; i < len; ++i) {
		free(g[i]);
	}
	free(g);
#endif

#endif
	return 0;
}
