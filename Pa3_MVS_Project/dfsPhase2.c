/*

*/
#include "scc03.c"
#include "dfsTrace1.h"
#include "dfsTrace1.c"
#include "intVec.h"
#include "loadGraph.h"
#include "dfsPhase2.h"
int rootCount = 0;

IntVec* dfsPhase2(IntVec *adjList, dfsData dfsInfo)
{
	IntVec *roots;
	roots = calloc(nodeCount + 1, sizeof(IntVec));
	/*only do this for roots
	for (int i = 0; i <= nodeCount; i++)
	{
		roots[i] = makeEmtpyVec();
	}
	*/
	int newRoot = 0;

	newRoot = dfsSweepT(dfsInfo);
	while (newRoot != -1)
	{
		roots[newRoot] = intMakeEmptyVec();
		//intVecPush(roots, newRoot); Replace with proper roots storage; 6/4 5pm-------------------------------------
		dfsTrace1(adjList, newRoot, dfsInfo, roots);
		newRoot = dfsSweepT(dfsInfo);
	}
	//process dfsInfo and into roots (type IntVec*)
	return roots;
}


int dfsSweepT(dfsData dfsInfo)//return the int value of a undiscovered vertex.
{
	
	int tempReturn = -1;
	int i = 1;
	while (1)
	{		
		if (strcmp(dfsInfo->color[i], 'W') == 0)
		{
			dfsInfo->parent[i] = -1;
			
			return i;
		}
		i++;
		if (i > nodeCount)
			return 0;
	}
}