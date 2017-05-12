/*
intVec.c
Ben Donn
bdonn
pa2
The following is the Integer vector node adt.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intVec.h"

	//Struct definitions----------------------------------------------------------------
	struct IntVecNode
	{
		int *data;
		int sz;
		int capacity;
	};

	//Variables-------------------------------------------------------------------------
	IntVec newVec;

	/* Access functions
	*/

	/** intTop()
	* (Preconditions: myVec->capacity != 0)
	*/
	int intTop(IntVec myVec)
	{
		if (myVec->capacity == 0) //if fails precondition.
		{
			fprintf(stderr, "Error: myVec->capacity==0");
			exit( 0);
		}
		return myVec->data[(myVec->sz) - 1]; //this used to be special
	}

	/** intData()
	* precondition: 0 <= i < intSize(myVec).
	*/
	int intData(IntVec myVec, int i)
	{
		int temp = 0;
		if (!(i >= 0 && i < myVec->sz)) //if precondition fails.
		{
			fprintf(stderr, "Error: (0 <= i < intSize(myVec)) not true.");
			exit( 0);
		}
		temp = myVec->data[i];
		return temp;
	}

	/** intSize()
	* precondition: myVec has been constructed.
	*/
	int intSize(IntVec myVec)
	{
		if (myVec == NULL) //if myVec hasn't been constructed.
		{
			fprintf(stderr, "Error: myVec==NULL.");
			exit( 0);
		}
		return myVec->sz;
	}

	/** intCapacity()
	* precondition: myVec has been constructed.
	*/
	int intCapacity(IntVec myVec)
	{
		if (myVec == NULL) //if myVec hasn't been constructed.
		{
			fprintf(stderr, "Error: myVec == NULL.");
			exit(0);
		}
		return myVec->capacity;
	}

	/* Constructors
	*/

	/** intMakeEmptyVec()
	* preconditions: none.
	* postconditions: Let /return be the value returned by intMakeEmptyVec().
	*    Then intCapacity(/return) == 4, intSize(/return) == 0).
	*/
	IntVec intMakeEmptyVec(void)
	{
		newVec = calloc(1, sizeof(struct IntVecNode));
		newVec->data = calloc(intInitCap, sizeof(int));
		newVec->sz = 0;
		newVec->capacity = intInitCap;
		return newVec;
	}

	/* Manipulation Procedures
	*/

	/** intVecPush()
	* precondition: myVec has been constructed.
	* postconditions: Let /sz/ = intSize(myVec) before the call.
	*                 Let /cap/ = intCapacity(myVec) before the call.
	*    Then after the call, intSize(myVec) == /sz/+1,
	*        and intTop(myVec) == newE and intData(myVec, /sz/) == newE.
	*    Also, for all 0 <= i < /sz/: intData(myVec, i) is unchanged.
	*    Also, if (/sz/+1) > /cap/, then after the call,
	*        intCapacity(myVec) = 2 * /cap/.
	*    otherwise, intCapacity(myVec) is unchanged.
	*/
	void intVecPush(IntVec myVec, int newE) //fixed
	{
		if (myVec == NULL) //if precondition fails.
		{
			fprintf(stderr, "Error: myVec == NULL");
			exit(EXIT_FAILURE);
		}
		//replacing 
		if (intSize(myVec) == intCapacity(myVec))
		{
			myVec->data = (int*)realloc(myVec->data, (sizeof(int) * (intSize(myVec)) * 2));//found her
			if (myVec->data == NULL) //if realloc failed.
			{
				fprintf(stderr, "Error: realloc failed");
				exit(EXIT_FAILURE);
			}
			myVec->capacity = (intCapacity(myVec)) * 2;
		}

		myVec->data[intSize(myVec)] = newE;

		//postconditions
		myVec->sz = (intSize(myVec)) + 1;
	}

	/** intVecPop()
	* precondition: myVec has been constructed and intSize(myVec) > 0.
	* postconditions: Let /sz/ = intSize(myVec) before the call.
	*                 Let /cap/ = intCapacity(myVec) before the call.
	*    Then after the call, intSize(myVec) == /sz/-1,
	*        intTop(myVec) == intData(/sz/-2).
	*    Also, for all 0 <= i < /sz/-1: intData(myVec, i) is unchanged.
	*    Also, intCapacity(myVec) is unchanged.
	*/
	void intVecPop(IntVec myVec) //fixed
	{
		if (myVec == NULL) //if precondition fails.
		{
			fprintf(stderr, "Error: myVec not constructed");
			exit(0);
		}
		myVec->data[(intSize(myVec) - 1)] = 0;
		myVec->sz = (intSize(myVec)) - 1;
	}
