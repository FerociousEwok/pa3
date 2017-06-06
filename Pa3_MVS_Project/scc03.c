/*
scc03.c
Ben Donn
bdonn
pa3

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "scc03.h"
#include "intVec.h"

#include "loadGraph.h"

#include "dfsTrace1.h"

#include "dfsPhase2.h"


int nodeCount = 0;
//IntVec finishStk1; should be in dfsTrace1.c struct now
//char *color; should be in dfsTrace1.c struct now



IntVec* findSCCs(IntVec *adjList, dfsData dfsInfo)//Todo: 2 things, 2 comments.; Also, dfs1Trace must take parameter roots also.
{
	IntVec *roots;//where the scc answer will go.
	int tempRoot = -1, newRoot2 = -1;
	IntVec *adjListT;//transposed
	dfsData dfsInfoT;//transposed
	adjListT = calloc(nodeCount, sizeof(IntVec));
	dfsInfoT = makeNewDfsDataObj(nodeCount);

	roots = calloc(nodeCount + 1, sizeof(IntVec));
	/* Vector should only be made if its a root, handle this in dfsPhase2.c
	for (int i = 1; i <= nodeCount; i++)
	{
		roots[i] = intMakeEmptyVec();
	}
	*/

	adjListT = transposeGraph(adjList, nodeCount);
	fprintf(stdout, "\n-----Transpose-----\n");
	printAdjVerts(adjListT, nodeCount);
	printAdjMatrix(makeAdjMatrix(adjListT, nodeCount), nodeCount);//formating my be needed in these lines.

	roots = dfsPhase2(adjListT, dfsInfoT);//------Formating probably needed for the below lines----
	printDfsData2(dfsInfoT, roots);
	return roots;
}

int main(int argc, char **argv)
{
	//variables
	FILE *inputFile = NULL;
	char *tempInputString = "";
	char *readMode = "r+";
	IntVec *adjList, *roots1;
	char *flag = "default", *userInput = "";
	dfsData dfsInfo;
	IntVec *sccList;
	
	
	
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
		//userInput = getc(stdin);//thats not how this should work. use scanf
		scanf("%s", userInput);
		tempInputString = userInput;
		fprintf(stdout, "\n");
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

	adjList = loadGraph(inputFile, nodeCount, flag);
	adjMatrix = makeAdjMatrix(adjList, nodeCount);
	printAdjVerts(adjList, nodeCount);
	if (nodeCount <= 20)
		printAdjMatrix(adjMatrix, nodeCount);

	roots1 = calloc(nodeCount + 1, sizeof(IntVec));
	dfsInfo = makeNewDfsDataObj(nodeCount);
	newRoot = dfsSweepT(dfsInfo);
	while (newRoot != -1)
	{

		dfsTrace1(adjList, newRoot, dfsInfo, roots1);//dfs starting at node newRoot
		newRoot = dfsSweepT(dfsInfo);
	}
	printDfsData(dfsInfo);
	fprintf(stdout, "\nFSTK: ");
	//while (intSize(getFinishStk(dfsInfo)) != 0)
	for(int i = 0; i< intSize(*getFinishStk(dfsInfo)); i++)//added star6/5:0352pm
	{
		fprintf(stdout, "%d  ", intData(*getFinishStk(dfsInfo), i));//added star^
	}
	fprintf(stdout, "\n");

	sccList = calloc(nodeCount, sizeof(IntVec));
	sccList = findSCCs(adjList, dfsInfo);

	fprintf(stdout, "Program completed with no errors, Press any key to exit: ");
	getc(stdin);
	return EXIT_SUCCESS;
}