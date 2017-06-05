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

IntVec* getFinishStk(dfsData dfsInfo)
{
	return dfsInfo->finishStk;
}

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
	for (int i = 1; i <= nodeCount; i++)//default:not a root
		dfsObj->parent[i] = -1;
	dfsObj->timeCount = 0;
	return dfsObj;
}

/**/
void printDfsData(dfsData dfsInfo)
{
	fprintf(stdout, "\nV    color  dTime  fTime  parent\n");
	for (int i = 1; i <= nodeCount; i++)//for each vector i.
	{
		fprintf(stdout, "%d    %s    %d    %d    %d", i, dfsInfo->color[i], dfsInfo->discoverTime[i], dfsInfo->finishTime[i], dfsInfo->parent[i]);
	}
	fprintf(stdout, "\n");
}

void printDfsData2(dfsData dfsInfoT, IntVec* roots)//for the scc
{
	int temp = 0;
	fprintf(stdout, "\nV    color2  dTime2  fTime2  parent2  dfsRoot2\n");
	for (int i = 1; i <= nodeCount; i++)//for each vector
	{
		/*
		for (int j = intSize(roots); j > 0; j--)//for each dfsRoot
		{
			for(int z = 1; z<= )
		}
		*/
		fprintf(stdout, "%d    %s    %d    %d    %d    %d\n", i, dfsInfoT->color[i], dfsInfoT->discoverTime[i], dfsInfoT->finishTime[i], dfsInfoT->parent[i], 69);//temp value for root till implemented
	}
	fprintf(stdout, "\n");
}

/**/
void dfsTrace1(IntVec adjVertices[], int v, dfsData dfsInfo, IntVec *roots) //v is the current node
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
			dfsInfo->parent[w] = v;
			dfsTrace1(adjVertices, w, dfsInfo, roots);
		}
		else
		{
			//implement recording that a cycle was reached here.
		}
		//remAdj = rest(remAdj); not sure what this means.
	}
	dfsInfo->finishTime[v] = dfsInfo->timeCount;
	dfsInfo->color[v] = 'B';
	intVecPush(dfsInfo->finishStk, v);
	return;
}