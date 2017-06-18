/*

*/
//#include "scc03.c" think this causes compile error, multiple mains
#include <stdio.h>
#include <stdlib.h>
#include "intVec.h"
#include "dfsTrace1.h"


#include "loadGraph.h"
#include "dfsPhase2.h"
#include "scc03.h"
int rootCount = 0;

IntVec* dfsPhase2(IntVec *adjList, dfsData dfsInfo)
{
	IntVec *roots = calloc(nodeCount + 1, sizeof(IntVec));
	

	for (int i = 0; i <= nodeCount; i++)
	{
		roots[i] = intMakeEmptyVec();
	}
	
	int newRoot = 0;

	newRoot = dfsSweepT(dfsInfo);
	while (newRoot != -1)
	{
		//intVecPush(roots, newRoot); Replace with proper roots storage; 6/4 5pm-------------------------------------
		dfsTrace1(adjList, newRoot, dfsInfo, roots, newRoot);
		newRoot = dfsSweepT(dfsInfo);
	}
	//process dfsInfo and into roots (type IntVec*)
	return roots;
}


int dfsSweepT(dfsData dfsInfo)//may be infinite loop here.
{
	
	int tempReturn = -1;
	int i = 1;
	while (1)
	{		
		if ( (dfsInfo->color[i]) == 'W')
		{
			dfsInfo->parent[i] = -1;
			
			return i;
		}
		i++;
		if (i > nodeCount)
			return tempReturn;
	}
}