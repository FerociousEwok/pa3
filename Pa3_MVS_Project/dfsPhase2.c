/*

*/
#include "scc03.c"
#include "dfsTrace1.h"
#include "dfsTrace1.c"
#include "intVec.h"
#include "loadGraph.h"
#include "dfsPhase2.h"

void dfsPhase2(IntVec *adjList, dfsData dfsInfo)
{
	IntVec *roots;
	int newRoot = 0;

	newRoot = dfsSweepT(dfsInfo);
	while (newRoot != -1)
	{
		dfsTrace1(adjList, newRoot, dfsInfo);
		newRoot = dfsSweepT(dfsInfo);
	}
	//process dfsInfo and into roots (type IntVec*)



	return;
}


int dfsSweepT(dfsData dfsInfo)//return the int value of a undiscovered vertex.
{
	int tempReturn = -1;
	int i = 1;
	while (1)
	{		
		if (strcmp(dfsInfo->color[i], 'W') == 0)
			return i;
		i++;
		if (i > nodeCount)
			return -1;
	}
}