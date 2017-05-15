/*
loadGraph.h
Ben Donn
bdonn
pa3
*/

#ifndef C101loadGraph
#define C101loadGraph
/*

*/
int** makeAdjMatrix(IntVec *adjList, int nodeCount);

/*

*/
IntVec* transposeGraph(IntVec *adjList, int n);

/*

*/
void printAdjVerts(IntVec *adjList, int nodeCount);

/**/
void printAdjMatrix(int **adjMatrix, int nodeCount);

/*

*/

IntVec* loadGraph(FILE *inputFile, int nodeCount, char *flag);

/*

*/
int getNodeCount(FILE *inputFile);

/*

*/
int getEdgeCount(IntVec *adjList);

#endif