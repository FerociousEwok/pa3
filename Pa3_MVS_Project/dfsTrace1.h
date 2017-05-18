/*



*/
#ifndef C101Trace
#define C101Trace
/*
*/
void dfsTrace1(IntVec adjVertices[], int v, dfsData dfsInfo);

/*
*/
typedef struct dfsDataObj * dfsData;

dfsData makeNewDfsDataObj(int nodeCount);

void printDfsData(dfsData dfsInfo);

void printDfsData2(dfsData dfsInfoT);
#endif