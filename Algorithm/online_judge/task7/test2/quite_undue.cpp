#include<iostream>
#include<assert.h>
using namespace std;

/*
Well, first of all, I want to say, it is quite undue this time.
This version is very simple. It just gets a array, gets the input data
and print one of its lines.
However, it is this simple code that the interesting OJ system judge TIME LIMIT EXCEEDED.
Hello? Are you drunk too much last night?
I don't know how to simplify this version. Maybe someone as clever as you can make it. I can't.
To be honest, I do NOT want to swear at all. But in my opinion, it is REALLY UNDUE this time.
*/

int main() {
	int len = 0;
	scanf("%d", &len);

	int **g = (int **)malloc(sizeof(int *) * len);	assert(g != NULL);
	for (int i = 0; i < len; ++i) {
		g[i] = (int *)malloc(sizeof(int) * len);	assert(g[i] != NULL);
		//for (int j = 0; j < len; ++j) {
		//	g[i][j] = 0;
		//}
	}
	//cout << "Hello" << endl;

	int begin = 0, end = 0, weight = 0;
	while (scanf("%d%d%d", &begin, &end, &weight) != EOF) {
		g[begin][end] = weight;
	}
/*
	int *path = (int *)malloc(sizeof(int) * len);	assert(path != NULL);
	for (int i = 0; i < len; ++i) {
		path[i] = g[0][i];
	}

	for (int i = 1; i < len; ++i) {
		printf("%d ", path[i]);
	}
	printf("\n");
*/
        for (int i = 0; i < len; ++i) {
                printf("%d ", i);
        }
        printf("\n");

	for (int i = 0; i < len; ++i) {
		free(g[i]);
	}
	free(g);

	return 0;
}

