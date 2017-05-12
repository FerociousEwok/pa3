/*
graph02.c
Ben Donn
bdonn
pa2
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intVec.h"
#include "loadGraph.h"

int main(int argc, char **argv)
{
	//variables
	FILE *inputFile = NULL;
	char *tempInputString = "";
	char *readMode = "r+";
	IntVec *adjList;
	char *flag = "default";
	int nodeCount = 0;
	int flagCheckOne = 0, flagCheckTwo = 0;

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

	fprintf(stdout, "FLAG == %s\n\n", flag);
	fprintf(stdout, "----Original adjList----\n\n");
	printAdjVerts(adjList, nodeCount);
	if (nodeCount <= 20)
		printAdjMatrix(makeAdjMatrix(adjList, nodeCount), nodeCount);
	for (int i = 0; i < 2; i++) //run twice; second transpose
	{
		adjList = transposeGraph(adjList, nodeCount); //adjList now transposedAdjList.
		i == 0? fprintf(stdout, "----First Transpose----\n\n")
			: fprintf(stdout, "----SecondTranspose----\n\n");
		printAdjVerts(adjList, nodeCount);
		if (nodeCount <= 20)
			printAdjMatrix(makeAdjMatrix(adjList, nodeCount), nodeCount);
	}

	//free allocated memory--------------------------------------------------------
	
	//for(int i = 0; i < nodeCount; i++)
		//if(adjList[i] != NULL)
			//free(adjList[i]);
	fprintf(stdout, "Program completed with no errors, Press any key to exit: ");
	getc(stdin);
	return EXIT_SUCCESS;
}