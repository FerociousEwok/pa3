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
	int timeCount;
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
	dfsObj->timeCount = 0;
	return dfsObj;
}

/**/
void printDfsData(dfsData dfsInfo)
{

}

void printDfsData2(dfsData dfsInfoT)//for the scc
{

}

/**/
void dfsTrace1(IntVec adjVertices[], int v, dfsData dfsInfo) //v is the current node
{
	
	IntVec vAdjs = adjVertices[v];
	int remAdjs, w;

	dfsInfo->timeCount += 1;
	dfsInfo->discoverTime[v] = dfsInfo->timeCount;
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
			//implement recording that a cycle was reached here.
		}
		//remAdj = rest(remAdj); not sure what this means.
	}
	dfsInfo->finishTime[v] = dfsInfo->timeCount;
	dfsInfo->color[v] = 'B';
	intVecPush(dfsInfo->finishStk, adjVertices[v]);
	return;
}