/*
will implement dfsTrace (Algorithm 7.4, which is a refinement of
Algorithm 7.3) on a directed graph represented as an array of
adjacency IntVecs.

*/
#include <string.h>
#include "intVec.h";
#include "scc03.c";


void dfsTrace1(IntVec adjVertices[], int v) //v is the current node
{
	
	IntVec vAdjs = adjVertices[v];
	int remAdjs, w;
	color[v] = "G";
	remAdjs = intSize(vAdjs);

	while (remAdjs > 0)
	{
		remAdjs--;
		w = intData(vAdjs, remAdjs);
		if (strcmp(color[w], "W"))
		{
			dfs(adjVertices, w);
		}
		else
		{

		}
		//remAdj = rest(remAdj); not sure what this means.
	}
	color[v] = "B";
	intVecPush(finishStk1, adjVertices[v]);
	return;
}