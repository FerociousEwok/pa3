/*
will implement dfsTrace (Algorithm 7.4, which is a refinement of
Algorithm 7.3) on a directed graph represented as an array of
adjacency IntVecs.

*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "intVec.h"
#include "dfsTrace1.h"
#include "scc03.h"

//#include "scc03.c" think this causes compile error.

/**/
typedef struct dfsDataObj dfsDataObj;
//typedef struct dfsDataObj *dfsData;



IntVec getFinishStk(dfsData dfsInfo)
{
	return dfsInfo->finishStk;
}

/**/
dfsData makeNewDfsDataObj(int nodeCount)
{
	dfsData dfsObj = calloc(1, sizeof(struct dfsDataObj));//changed from dfsData
	dfsObj->discoverTime = calloc(nodeCount+1, sizeof(int));
	dfsObj->finishTime = calloc(nodeCount+1, sizeof(int));
	dfsObj->parent = calloc(nodeCount+1, sizeof(int));

	dfsObj->finishStk = intMakeEmptyVecN(nodeCount);//memory pointed to by finishStk set to be a vector obj
	dfsObj->color = calloc(nodeCount+1, sizeof(char));
	for (int i = 1; i <= nodeCount; i++)
		dfsObj->color[i] = 'W';
	for (int i = 1; i <= nodeCount; i++)//default:not a root
		dfsObj->parent[i] = 1;//changed from -1
	dfsObj->timeCount = 0;
	return dfsObj;
}

/**/
void printDfsData(dfsData dfsInfo)
{
	fprintf(stdout, "\n V  color     dTime    fTime      parent\n");
	for (int i = 1; i <= nodeCount; i++)//for each vector i.
	{
		fprintf(stdout, "%2d    %c        %2d        %2d        %2d\n", i, dfsInfo->color[i], dfsInfo->discoverTime[i], dfsInfo->finishTime[i], dfsInfo->parent[i]);
	}
	fprintf(stdout, "\n");
}

void printDfsData2(dfsData dfsInfoT, IntVec* roots)//for the scc
{
	int temp = 0;
	fprintf(stdout, "\n V  color2   dTime2    fTime2    parent2   dfsRoot2\n");
	for (int i = 1; i <= nodeCount; i++)//for each vector
	{
		/*
		for (int j = intSize(roots); j > 0; j--)//for each dfsRoot
		{
			for(int z = 1; z<= )
		}
		*/
		fprintf(stdout, "%2d    %c        %2d        %2d        %2d        ", i, dfsInfoT->color[i], dfsInfoT->discoverTime[i], dfsInfoT->finishTime[i], dfsInfoT->parent[i]);
		
		for (int j = 1; j <= nodeCount; j++)//for each root of the dfs tree
		{
				for (int z = 0; z < intSize(roots[j]); z++)//for each value in current roots data array
				{
					if (i == intData(roots[j], z))//if current vector i is a root of j
					{
						fprintf(stdout, "%2d", j);
					}
				}
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "\nFSTK: ");
	//while (intSize(getFinishStk(dfsInfo)) != 0)
	for (int i = 0; i< intSize(getFinishStk(dfsInfoT)); i++)//added star6/5:0352pm
	{
		fprintf(stdout, "%d  ", intData(getFinishStk(dfsInfoT), i));//added star^
	}
	fprintf(stdout, "\n");
}

/**/
void dfsTrace1(IntVec* adjVertices, int v, dfsData dfsInfo, IntVec *roots, int currentRoot) //v is the current node
{
	
	IntVec vAdjs = adjVertices[v];
	int remAdjs, w;
	

	dfsInfo->timeCount += 1;
	dfsInfo->discoverTime[v] = dfsInfo->timeCount;
	dfsInfo->color[v] = 'G';
	remAdjs = intSize(vAdjs);

	intVecPush(roots[currentRoot], v);

	while (remAdjs > 0)
	{
		remAdjs--;
		w = intData(vAdjs, remAdjs);
		if (dfsInfo->color[w] == 'W')//compares two characters by asci value
		{
			dfsInfo->parent[w] = v;
			dfsTrace1(adjVertices, w, dfsInfo, roots, currentRoot);
		}
		else
		{
			//implement recording that a cycle was reached here.
		}
		//remAdj = rest(remAdj); not sure what this means.
	}
	dfsInfo->timeCount += 1;
	dfsInfo->finishTime[v] = dfsInfo->timeCount;
	dfsInfo->color[v] = 'B';
	intVecPush(dfsInfo->finishStk, v);
	return;
}