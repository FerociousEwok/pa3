/*
scc03.c
Ben Donn
bdonn
pa3

HIGH-LEVEL FLOW

main() should read and interpret the command-line parameters, which
are different from in pa02, then open the input file and interact with
loadGraph.c functions to input the graph, as in pa02.
Then call your function to convert the array of adjacency lists to
the 2-D adjacency matrix, as in pa02.

main() should call a function to print the graph, as in pa02.
As in pa02, when n <= 20 vertices print the  adjacency matrix also.

To compute SCCs, main calls a function with a name like findSCCs()
that is also in scc03.c to manage the SCC computation.
findSCCs() should call the main subroutines dfsTrace1(),
transposeGraph(), dfsPhase2(), as well as calling the printing functions.
IN PARTICULAR, dfsTrace1(), transposeGraph(), dfsPhase2() WILL NOT PRINT
ANYTHING.  Their job is to compute data structures.

findSCCs() in scc03.c will allocate the arrays filled by its subroutines.
Because there are two runs of dfsTrace now, name the arrays filled by
dfsTrace1(): discoverTime1, finishTime1, parent1, and finishStk1,
or recognizable abbreviations, such as dtime1, etc.

Also findSCCs() allocates adjVerticesT for the transpose graph.
Finally, it will allocate the arrays filled by the second dfs,
which works on the transpose graph and finds the SCCs:
discoverTime2, finishTime2, parent2, dfstRoot2 (or abbreviations).
Other procedures will output the contents of the arrays after
each dfsTrace has completed.

Allocating all the arrays in scc03.c makes it easier to pass them as
arguments to functions in other files, without making any global arrays.
However, if you already have working code that allocates and returns
an array from a different file (such as loadGraph.c)
it is okay to use and build upon that code.

A more sophisticated way to pass several run-time parameters is that
main() or findSCCs() creates a struct with fields for all of them,
and then a pointer to that struct is passed around.
For this technique you should declare the struct AS A TYPE in scc03.h.
Then scc03.c and loadGraph.c and maybe others #include scc03.h.

Write dfsTrace1.h to declare the function prototypes in dfsTrace1.c that
are called from a different C file.  State the pre- and post-conditions
in dfsTrace1.h.

In pa03 dfsTrace1.c should be a separate file and you should have it
working before copying it into dfsPhase2.c as a starter.
It is better to copy working code than debug both versions.

Aside from intVec.h, intVec.c, scc03.c and scc03, the names of files,
functions and arrays should be understandable but do NOT need to be
strictly the same as this handout.

TODO: make dfsData struct to store information in multiple arrays in the struct.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intVec.h"
#include "loadGraph.h"
#include "dfsTrace1.h"
#include "dfsPhase2.h"
int nodeCount = 0;
//IntVec finishStk1; should be in dfsTrace1.c struct now
//char *color; should be in dfsTrace1.c struct now



IntVec* findSCCs(IntVec *adjList, dfsData dfsInfo)//this function should handle printing.
{
	IntVec *roots;//where the scc answer will go.
	int tempRoot = -1;
	IntVec *adjListT;//transposed
	dfsData dfsInfoT;//transposed
	adjListT = calloc(nodeCount, sizeof(IntVec));
	dfsInfoT = makeNewDfsDataObj(nodeCount);
	roots = calloc(nodeCount, sizeof(IntVec));

	adjListT = transposeGraph(adjList, nodeCount);


	return roots;
}

int main(int argc, char **argv)
{
	//variables
	FILE *inputFile = NULL;
	char *tempInputString = "";
	char *readMode = "r+";
	IntVec *adjList;
	char *flag = "default";
	dfsData dfsInfo;
	IntVec *sccList;
	
	
	int flagCheckOne = 0, flagCheckTwo = 0;
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
	inputFile = fopen(tempInputString, readMode);
	if (inputFile == 0)
	{
		fprintf(stderr, "fopen() error\nPress any key to close: ");
		getc(stdin);
		exit(1);
	}
	/*NEW COMMAND LINE CHECK:(if user wants to type in file name)

	*/


	nodeCount = getNodeCount(inputFile);
	flagCheckOne = strcmp(flag, "-U");
	flagCheckTwo = strcmp(flag, "default");
	if (flagCheckOne != 0 && flagCheckTwo != 0)//if bad command line input
	{
		fprintf(stderr, "Error reading command line input\nPress any key to close: ");
		getc(stdin);
		exit(1);
	}


//Todo: Change below code to function for new dfsData obj implementation--------------
	

	adjList = loadGraph(inputFile, nodeCount, flag);
	adjMatrix = makeAdjMatrix(adjList, nodeCount);
	printAdjVerts(adjList, nodeCount);
	if (nodeCount <= 20)
		printAdjMatrix(adjMatrix, nodeCount);

	dfsInfo = makeNewDfsDataObj(nodeCount);
	
	
	dfsTrace1(adjList, 1, dfsInfo);//dfs starting at node 1
	printDfsData(dfsInfo);

	sccList = calloc(nodeCount, sizeof(IntVec));
	sccList = findSCCs(adjList, dfsInfo);




/*MAIN FOR PA2
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
*/
	//free allocated memory-------------------
	//for(int i = 0; i < nodeCount; i++)
		//if(adjList[i] != NULL)
			//free(adjList[i]);
	fprintf(stdout, "Program completed with no errors, Press any key to exit: ");
	getc(stdin);
	return EXIT_SUCCESS;
}