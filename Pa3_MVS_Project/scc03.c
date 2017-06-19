/*
scc03.c
Ben Donn
bdonn
pa3

This is the main file for pa3. This project calculates strongly connected components of a graph by transposing a graph and running depth first search on it.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intVec.h"

#include "scc03.h"

#include "loadGraph.h"

#include "dfsTrace1.h"

#include "dfsPhase2.h"


int nodeCount = 0;

IntVec* findSCCs(IntVec *adjList, dfsData dfsInfo)
{
	IntVec *roots;//where the scc answer will go.
	int tempRoot = -1, newRoot2 = -1;
	IntVec *adjListT;//transposed
	dfsData dfsInfoT;//transposed
	adjListT = calloc(nodeCount+1, sizeof(IntVec));
	dfsInfoT = makeNewDfsDataObj(nodeCount);

	adjListT = transposeGraph(adjList, nodeCount);
	fprintf(stdout, "\n-----Transpose-----\n");
	printAdjVerts(adjListT, nodeCount);
	printAdjMatrix(makeAdjMatrix(adjListT, nodeCount), nodeCount);

	roots = dfsPhase2(adjListT, dfsInfoT);
	
	printDfsData2(dfsInfoT, roots);

	for (int i = 1; i <= nodeCount; i++)
	{
		free(adjListT[i]);
	}
	free(adjListT);
	
	free(dfsInfoT->color);
	free(dfsInfoT->discoverTime);
	free(dfsInfoT->finishTime);
	free(dfsInfoT->parent);
	free(dfsInfoT->finishStk);
	free(dfsInfoT);

	return roots;
}

void main(int argc, char **argv)
{
	//variables
	FILE *inputFile = NULL;
	char *tempInputString="ThisIsBlankSpaceToHoldMemoeryblahblahblahblahblahblahblahblahblahblahblahblah";
	const char *readMode = "r+";
	IntVec *adjList, *roots1;
	char *flag = "default", *userInput;
	dfsData dfsInfo;
	IntVec *sccList;
	
	//Input Checking------------------------------------------
	
	int flagCheckOne = 0, flagCheckTwo = 0, newRoot = 0;
	int** adjMatrix;

	if (argc == 1) //no command line argument
	{
		fprintf(stderr, "Error: no command line arguments.\nPress any key to close: ");
		getc(stdin);
		exit(0);
	}
	else if (argc == 2) //if there is not a -U flag
		tempInputString = argv[1];
	else if (argc == 3) //flag given
	{
		flag = argv[1];
		tempInputString = argv[2];
	}
	if (strcmp(tempInputString, "-") == 0)
	{		
		fprintf(stdout, "\nPlease type a file name(Up to 25 characters): ");
		userInput = calloc(25, sizeof(char));
		
		scanf("%s", userInput);
		tempInputString = userInput;
		fprintf(stdout, "\n");
		free(userInput);
	}
	
	inputFile = fopen(tempInputString, readMode);
	if (inputFile == 0)
	{
		fprintf(stderr, "fopen() error\nPress any key to close: ");
		getc(stdin);
		exit(1);
	}

	nodeCount = getNodeCount(inputFile);
	flagCheckOne = strcmp(flag, "-U");
	flagCheckTwo = strcmp(flag, "default");
	if (flagCheckOne != 0 && flagCheckTwo != 0)//if bad command line input
	{
		fprintf(stderr, "Error reading command line input\nPress any key to close: ");
		getc(stdin);
		exit(1);
	}

	//Main function tasks here

	adjList = loadGraph(inputFile, nodeCount, flag);
	
	adjMatrix = makeAdjMatrix(adjList, nodeCount);
	printAdjVerts(adjList, nodeCount);
	if (nodeCount <= 20)
		printAdjMatrix(adjMatrix, nodeCount);

	roots1 = calloc(nodeCount + 1, sizeof(IntVec));
	for (int a = 1; a <= nodeCount; a++)
		roots1[a] = intMakeEmptyVec();

	dfsInfo = makeNewDfsDataObj(nodeCount);
	newRoot = dfsSweepT(dfsInfo);
	while (newRoot != -1)
	{
		dfsTrace1(adjList, newRoot, dfsInfo, roots1, newRoot);//dfs starting at node newRoot
		newRoot = dfsSweepT(dfsInfo);
	}
	printDfsData(dfsInfo);
	fprintf(stdout, "\nFSTK: ");
	
	for(int i = 0; i< intSize(getFinishStk(dfsInfo)); i++)
	{
		fprintf(stdout, "%d  ", intData(getFinishStk(dfsInfo), i));
	}
	fprintf(stdout, "\n");

	sccList = calloc(nodeCount, sizeof(IntVec));
	sccList = findSCCs(adjList, dfsInfo);
	//free alocated mem--------------------------------
	
	for (int i = 1; i <= nodeCount; i++)
	{
		free(adjList[i]);
	}
	free(adjList);
	free(dfsInfo->color);
	free(dfsInfo->discoverTime);
	free(dfsInfo->finishTime);
	free(dfsInfo->parent);
	free(dfsInfo->finishStk);
	free(dfsInfo);

	for (int i = 1; i <= nodeCount; i++)
	{
		free(sccList[i]);
	}
	free(sccList);
	for (int i = 0; i <= nodeCount; i++)
		free(adjMatrix[i]);
	free(adjMatrix);
	free(inputFile);
	
	fprintf(stdout, "Program completed with no errors, Press any key to exit: ");
	getc(stdin);
}