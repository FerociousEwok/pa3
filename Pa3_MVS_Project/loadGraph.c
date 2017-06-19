#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intVec.h"
#include "loadGraph.h"
/*
loadGraph.c
Ben Donn
bdonn
pa3

This file handles printing, and proccessing of user input.
*/
int globalEdgeCount = 0;

int** makeAdjMatrix(IntVec *adjList, int nodeCount)
{
	int** adjMatrix = calloc(nodeCount+1, sizeof(int *));
	int dataValue = 0;
	for (int i = 0; i <= nodeCount; i++)
		adjMatrix[i] = calloc(nodeCount+1, sizeof(int));

	for (int i = 1; i <= nodeCount; i++)//for each node. i.e. each index of array.
	{
		for (int j = 1; j <= nodeCount; j++) //for each node that adjList[i] could have an edge to.
		{
			for (int z = 0; z < intSize(adjList[i]); z++) //for each element in adjList[i]->data
			{
				dataValue = intData(adjList[i], z);
				if (dataValue == j)//if adjList[i] has edge to adjList[j]
				{
					adjMatrix[i][j] = 1;
				}
				else if(adjMatrix[i][j] != 1)
				{
					adjMatrix[i][j] = 0;
				}
			}
		}
	}
	return adjMatrix;
}

IntVec* transposeGraph(IntVec* adjList, int n)
{
	int data = 0;
	IntVec *transposedList = calloc(n+1, sizeof(IntVec));
	for (int i = 0; i <= n; i++) //initialize a new array of vectors.
	{
		transposedList[i] = intMakeEmptyVec();
	}

	for (int i = 1; i <= n; i++)//traverse through adjList data
	{
		for (int j = 0; j < intSize(adjList[i]); j++)//for each element in adjList[i]->data
		{
			data = intData(adjList[i], j);
			if(data >=0)
				intVecPush(transposedList[data], i);//transpose from adjList to new vector array.
		}
	}
	return transposedList;
}

void printAdjVerts(IntVec *adjList, int nodeCount)
{
	int n = nodeCount, m = 0, data = 0;
	int debug = 0;
	m = getEdgeCount(adjList);

	fprintf(stdout, "nodeCount = %d\nedgeCount = %d\n\n", n, m);
	for (int w = 1; w <= n; w++) //for each node
	{
		fprintf(stdout, " %2d  [", (w));
		for (int u = 0; u < intSize(adjList[w]); u++) //for each edge from that node
		{
			data = intData(adjList[w], u);
			fprintf(stdout, "%2d", data);
			if (u < intSize(adjList[w]) - 1) //if its not the last element
				fprintf(stdout, ", ");
		}
		fprintf(stdout, "]\n");
	}
	fprintf(stdout, "\n");
}

void printAdjMatrix(int** adjMatrix, int nodeCount)
{
	fprintf(stdout, "Matrix:\n");
	fprintf(stdout, "        ");
	for (int i = 1; i <= nodeCount; i++)
	{
		fprintf(stdout, "%2d   ", i);
	}
	fprintf(stdout, "\n");
	for (int i = 1; i <= nodeCount; i++) //for each adjList[i]
	{
		fprintf(stdout, "\n  %2d :  ", i);
		for (int j = 1; j <= nodeCount; j++) //for each potential edge
		{
			if(adjMatrix[i][j] == 0 || adjMatrix[i][j] == 1)//needed in case where intSize(vector) == 0
				fprintf(stdout, "%2d   ", adjMatrix[i][j]);
			else
				fprintf(stdout, "0  ");
		}
	}
	fprintf(stdout, "\n\n");
}


/*
The below function callocs an array of vectors and fills it based on inputFile
	then returns a pointer to the array.
*/
IntVec* loadGraph(FILE *inputFile, int nodeCount, char* flag)
{
	//local variables
	int *tempInt, *dataValue, equal = 0;
	float *weight;
	IntVec *tempList;
	char *lineOfFile;
	//begin the calloc's-------------------------------------------------
	lineOfFile = calloc(30, sizeof(char));
	weight = calloc(1, sizeof(float));
	tempInt = calloc(1, sizeof(int));
	dataValue = calloc(1, sizeof(int));
	
	tempList = calloc(nodeCount + 1, sizeof(IntVec));
	for (int i = 0; i <= nodeCount; i++)
		tempList[i] = intMakeEmptyVec();
	while ((fgets(lineOfFile, 20, inputFile) != NULL)) //for each line of the file.
	{
		if (lineOfFile[0] == '\n') //if fgets needed to clear newline character
			fgets(lineOfFile, 20, inputFile);
		sscanf(lineOfFile, "%d %d %f", tempInt, dataValue, weight);

		intVecPush(tempList[*tempInt], *dataValue);
		globalEdgeCount++;
		equal = strcmp(flag, "-U");
		if (equal == 0) //if undirected
		{
			intVecPush(tempList[*dataValue], *tempInt);
			globalEdgeCount++;
		}
	}
	return tempList;
}

int getNodeCount(FILE *inputFile) //Only call once or there might be errors.
{
	int temp = 0;
	char *tempString = calloc(5, sizeof(char));
	fgets(tempString, 5, inputFile);
	temp = atoi(tempString);
	return temp;
}

int getEdgeCount(IntVec *adjList) //Can call multiple times.
{
	return globalEdgeCount;
	
}