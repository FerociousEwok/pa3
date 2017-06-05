/*



*/
#ifndef C101Trace
#define C101Trace
/*
*/


/*
*/
typedef struct dfsDataObj * dfsData;

void dfsTrace1(IntVec adjVertices[], int v, dfsData dfsInfo, IntVec *roots);

dfsData makeNewDfsDataObj(int nodeCount);

void printDfsData(dfsData dfsInfo);

void printDfsData2(dfsData dfsInfoT, IntVec* roots);

IntVec* getFinishStk(dfsData dfsInfo);
#endif