/*
will implement dfsTrace (Algorithm 7.4, which is a refinement of
Algorithm 7.3) on a directed graph represented as an array of
adjacency IntVecs.

*/
#include <string.h>
#include "intVec.h"
#include "scc03.c"

/**/
struct dfsDataObj
{
	int *discoverTime, *finishTime, *parent;
	IntVec *finishStk;
	char *color;
};

/**/
dfsData makeNewDfsDataObj(int nodeCount)
{
	dfsData dfsObj = calloc(1, sizeof(dfsData));
	dfsObj->discoverTime = calloc(nodeCount, sizeof(int));
	dfsObj->finishTime = calloc(nodeCount, sizeof(int));
	dfsObj->parent = calloc(nodeCount, sizeof(int));
	dfsObj->finishStk = intMakeEmptyVecN(nodeCount);//calloc( nodeCount, sizeof(IntVec));
	dfsObj->color = calloc(nodeCount, sizeof(char));
	for (int i = 1; i <= nodeCount; i++)
		dfsObj->color[i] = 'W';
	return dfsObj;
}



/**/
void dfsTrace1(IntVec adjVertices[], int v, dfsData dfsInfo) //v is the current node
{
	
	IntVec vAdjs = adjVertices[v];
	int remAdjs, w;
	dfsInfo->color[v] = 'G';
	remAdjs = intSize(vAdjs);

	while (remAdjs > 0)
	{
		remAdjs--;
		w = intData(vAdjs, remAdjs);
		if (strcmp(dfsInfo->color[w], 'W'))
		{
			dfsTrace1(adjVertices, w, dfsInfo);
		}
		else
		{

		}
		//remAdj = rest(remAdj); not sure what this means.
	}
	dfsInfo->color[v] = 'B';
	intVecPush(dfsInfo->finishStk, adjVertices[v]);
	return;
}