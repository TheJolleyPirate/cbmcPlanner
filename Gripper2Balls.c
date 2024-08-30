#include<stdio.h>
#include <stdlib.h>
int nondet_Int();

//starting condition
// state
int n = 20;
char state[20];
// reserve state[0] to always be 0
int nextIndex = 1;
// objects
int objects[] = {0, 1, 2};
int balls[] = {0, 1};
int grippers[] = {2};
//set predicate sizes;
int inRoom1[3];
int inRoom2[3];
int holding[3];
int empty[3];
// get index functions
int getIndexInRoom1(int x, int set) {
	int index;
	if (inRoom1[x] < 0) {
		if (set) {
			if (nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			inRoom1[x] = index;
		}
		else {
			index = 0;
		}
	}
	else {
		index = inRoom1[x];
	}
	return index;
}
int getIndexInRoom2(int x, int set) {
	int index;
	if (inRoom2[x] < 0) {
		if (set) {
			if (nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
				nextIndex += 1;
				inRoom2[x] = index;
		}
		else {
			index = 0;
		}
	}
	else {
		index = inRoom2[x];
	}
	return index;
}
int getIndexHolding(int x, int set) {
	int index;
	if (holding[x] < 0) {
		if (set) {
			if (nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
				nextIndex += 1;
				holding[x] = index;
		}
		else {
			index = 0;
		}
	}
	else {
		index = holding[x];
	}
	return index;
}
int getIndexEmpty(int x, int set) {
	int index;
	if (empty[x] < 0) {
		if (set) {
			if (nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
				nextIndex += 1;
				empty[x] = index;
		}
		else {
			index = 0;
		}
	}
	else {
		index = empty[x];
	}
	return index;
}
//action functions
void pickUp(int objectNum1) {
	if (state[getIndexEmpty(0, 0)] && ((state[getIndexInRoom1(objectNum1, 0)] && state[getIndexInRoom1(2, 0)]) || (state[getIndexInRoom2(objectNum1, 0)] && state[getIndexInRoom2(2, 0)]))) {
		state[getIndexEmpty(0, 0)] = 0;
		state[getIndexInRoom1(objectNum1, 0)] = 0;
		state[getIndexInRoom2(objectNum1, 0)] = 0;
		state[getIndexHolding(objectNum1, 1)] = 1;
	}
	return;
}
void moveRoom1() {
	state[getIndexInRoom2(2, 0)] = 0;
	state[getIndexInRoom1(2, 1)] = 1;
	return;
}
void moveRoom2() {
	state[getIndexInRoom1(2, 0)] = 0;
	state[getIndexInRoom2(2, 1)] = 1;
	return;
}
void putDownRoom1(int objectNum1) {
	if (state[getIndexHolding(objectNum1, 0)] && state[getIndexInRoom1(2, 0)]) {
		state[getIndexHolding(objectNum1, 0)] = 0;
		state[getIndexEmpty(0, 1)] = 1;
		state[getIndexInRoom1(objectNum1, 1)] = 1;
	}
	return;
}
void putDownRoom2(int objectNum1) {
	if (state[getIndexHolding(objectNum1, 0)] && state[getIndexInRoom2(2, 0)]) {
		state[getIndexHolding(objectNum1, 0)] = 0;
		state[getIndexEmpty(0, 1)] = 1;
		state[getIndexInRoom2(objectNum1, 1)] = 1;
	}
	return;
}
int main() {
	for (int i = 0; i < 3; i++) {
		inRoom1[i] = -1;
	}
	for (int i = 0; i < 3; i++) {
		inRoom2[i] = -1;
	}
	for (int i = 0; i < 3; i++) {
		holding[i] = -1;
	}
	for (int i = 0; i < 3; i++) {
		empty[i] = -1;
	}
	state[getIndexInRoom1(0, 1)] = 1;
	state[getIndexInRoom1(1, 1)] = 1;
	state[getIndexInRoom1(2, 1)] = 1;
	state[getIndexEmpty(0, 1)] = 1;
	int actionDecision;
	//have multiple indices, per max number of attributes in actions
	int index1;
	while (1 == 1) {
		//get decision variables
		actionDecision = nondet_Int();
		//choose an action
		switch (actionDecision) {
		case 1:
			index1 = nondet_Int();
			if (index1 >= 0 && index1 <= 1) {
				pickUp(balls[index1]);
			}
			break;
		case 2:
			moveRoom1();
			break;
		case 3:
			moveRoom2();
			break;
		case 4:
			index1 = nondet_Int();
			if (index1 >= 0 && index1 <= 1) {
				putDownRoom1(balls[index1]);
			}
			break;
		case 5:
			index1 = nondet_Int();
			if (index1 >= 0 && index1 <= 1) {
				putDownRoom2(balls[index1]);
			}
			break;
		}
		//check to see if goal state has been reached
		if (state[getIndexInRoom2(0, 0)] == 1 && state[getIndexInRoom2(1, 0)] == 1) {
			__CPROVER_assert(1 == 0, "FAIL MEANS SUCCESS");
		}
	}
}