/*



*/
#ifndef C101Trace
#define C101Trace
/*
*/
void dfsTrace1(IntVec adjVertices[], int v);

/*
*/
typedef struct dfsDataObj * dfsData;

dfsData makeNewDfsDataObj(int nodeCount);


#endif