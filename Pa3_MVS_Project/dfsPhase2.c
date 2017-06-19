/*
dfsPhase2.c
Ben Donn
pa3
This file contains sweep function to find new roots and dfsPhase2() which runs on the transposed graph and calculates scc.
*/

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
		
		dfsTrace1(adjList, newRoot, dfsInfo, roots, newRoot);
		newRoot = dfsSweepT(dfsInfo);
	}
	
	return roots;
}


int dfsSweepT(dfsData dfsInfo)
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