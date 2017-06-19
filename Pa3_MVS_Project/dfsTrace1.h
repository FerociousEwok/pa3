/*
dfsTrace1.h
Ben Donn
pa3
*/
#ifndef C101Trace
#define C101Trace

struct dfsDataObj {
	int *discoverTime, *finishTime, *parent;
	int timeCount;
	IntVec finishStk;
	char *color;
};

typedef struct dfsDataObj * dfsData;

void dfsTrace1(IntVec* adjVertices, int v, dfsData dfsInfo, IntVec* roots, int currentRoot);//changed first intvec to intvec*

dfsData makeNewDfsDataObj(int nodeCount);

void printDfsData(dfsData dfsInfo);

void printDfsData2(dfsData dfsInfoT, IntVec* roots);

IntVec getFinishStk(dfsData dfsInfo);

#endif