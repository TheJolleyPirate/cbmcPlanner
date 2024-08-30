#include<stdio.h>
#include <stdlib.h>
int nondet_Int();
//problem definition
//state
int n = 1892;
char state[1892];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
//predicates
int on[30][30];
int ontable[30];
int clear[30];
int handempty;
int holding[30];
int equals[30][30];

//get index functions
int getIndex_on(int x0, int x1, int set){
	int index;
	if(on[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			on[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = on[x0][x1];
	}
	return index;
}
int getIndex_ontable(int x0, int set){
	int index;
	if(ontable[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			ontable[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = ontable[x0];
	}
	return index;
}
int getIndex_clear(int x0, int set){
	int index;
	if(clear[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			clear[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = clear[x0];
	}
	return index;
}
int getIndex_handempty(int set){
	int index;
	if(handempty < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			handempty = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = handempty;
	}
	return index;
}
int getIndex_holding(int x0, int set){
	int index;
	if(holding[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			holding[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = holding[x0];
	}
	return index;
}
int getIndex_equals(int x0, int x1, int set){
	int index;
	if(equals[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			equals[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = equals[x0][x1];
	}
	return index;
}

//actions functions
void pick_up(int x){
	if(state[getIndex_clear(x, 0)] && state[getIndex_ontable(x, 0)] && state[getIndex_handempty(0)]){
		state[getIndex_ontable(x, 1)] = 0;
		state[getIndex_clear(x, 1)] = 0;
		state[getIndex_handempty(1)] = 0;
		state[getIndex_holding(x, 1)] = 1;
	}
	return;
}
void put_down(int x){
	if(state[getIndex_holding(x, 0)]){
		state[getIndex_holding(x, 1)] = 0;
		state[getIndex_clear(x, 1)] = 1;
		state[getIndex_handempty(1)] = 1;
		state[getIndex_ontable(x, 1)] = 1;
	}
	return;
}
void stack(int x, int y){
	if(state[getIndex_holding(x, 0)] && state[getIndex_clear(y, 0)]){
		state[getIndex_holding(x, 1)] = 0;
		state[getIndex_clear(y, 1)] = 0;
		state[getIndex_clear(x, 1)] = 1;
		state[getIndex_handempty(1)] = 1;
		state[getIndex_on(x, y, 1)] = 1;
	}
	return;
}
void unstack(int x, int y){
	if(state[getIndex_on(x, y, 0)] && state[getIndex_clear(x, 0)] && state[getIndex_handempty(0)]){
		state[getIndex_clear(x, 1)] = 0;
		state[getIndex_handempty(1)] = 0;
		state[getIndex_on(x, y, 1)] = 0;
		state[getIndex_holding(x, 1)] = 1;
		state[getIndex_clear(y, 1)] = 1;
	}
	return;
}
//main loop
int main(){
	//setting on to -1
	for(int i0 = 0; i0 < 30; i0++){
		for(int i1 = 0; i1 < 30; i1++){
			on[i0][i1] = -1;
		}
	}
	//setting ontable to -1
	for(int i0 = 0; i0 < 30; i0++){
		ontable[i0] = -1;
	}
	//setting clear to -1
	for(int i0 = 0; i0 < 30; i0++){
		clear[i0] = -1;
	}
	//setting handempty to -1
	handempty = -1;
	//setting holding to -1
	for(int i0 = 0; i0 < 30; i0++){
		holding[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 30; i0++){
		for(int i1 = 0; i1 < 30; i1++){
			equals[i0][i1] = -1;
		}
	}
	state[getIndex_clear(29, 1)] = 1;
	state[getIndex_clear(28, 1)] = 1;
	state[getIndex_clear(27, 1)] = 1;
	state[getIndex_clear(26, 1)] = 1;
	state[getIndex_clear(25, 1)] = 1;
	state[getIndex_clear(24, 1)] = 1;
	state[getIndex_clear(23, 1)] = 1;
	state[getIndex_ontable(29, 1)] = 1;
	state[getIndex_ontable(22, 1)] = 1;
	state[getIndex_ontable(21, 1)] = 1;
	state[getIndex_ontable(20, 1)] = 1;
	state[getIndex_ontable(19, 1)] = 1;
	state[getIndex_ontable(18, 1)] = 1;
	state[getIndex_ontable(23, 1)] = 1;
	state[getIndex_on(28, 17, 1)] = 1;
	state[getIndex_on(17, 16, 1)] = 1;
	state[getIndex_on(16, 15, 1)] = 1;
	state[getIndex_on(15, 14, 1)] = 1;
	state[getIndex_on(14, 13, 1)] = 1;
	state[getIndex_on(13, 12, 1)] = 1;
	state[getIndex_on(12, 22, 1)] = 1;
	state[getIndex_on(27, 11, 1)] = 1;
	state[getIndex_on(11, 21, 1)] = 1;
	state[getIndex_on(26, 10, 1)] = 1;
	state[getIndex_on(10, 9, 1)] = 1;
	state[getIndex_on(9, 8, 1)] = 1;
	state[getIndex_on(8, 7, 1)] = 1;
	state[getIndex_on(7, 6, 1)] = 1;
	state[getIndex_on(6, 5, 1)] = 1;
	state[getIndex_on(5, 4, 1)] = 1;
	state[getIndex_on(4, 20, 1)] = 1;
	state[getIndex_on(25, 3, 1)] = 1;
	state[getIndex_on(3, 2, 1)] = 1;
	state[getIndex_on(2, 1, 1)] = 1;
	state[getIndex_on(1, 0, 1)] = 1;
	state[getIndex_on(0, 19, 1)] = 1;
	state[getIndex_on(24, 18, 1)] = 1;
	state[getIndex_handempty(1)] = 1;
	state[getIndex_equals(0, 0, 1)] = 1;
	state[getIndex_equals(1, 1, 1)] = 1;
	state[getIndex_equals(2, 2, 1)] = 1;
	state[getIndex_equals(3, 3, 1)] = 1;
	state[getIndex_equals(4, 4, 1)] = 1;
	state[getIndex_equals(5, 5, 1)] = 1;
	state[getIndex_equals(6, 6, 1)] = 1;
	state[getIndex_equals(7, 7, 1)] = 1;
	state[getIndex_equals(8, 8, 1)] = 1;
	state[getIndex_equals(9, 9, 1)] = 1;
	state[getIndex_equals(10, 10, 1)] = 1;
	state[getIndex_equals(11, 11, 1)] = 1;
	state[getIndex_equals(12, 12, 1)] = 1;
	state[getIndex_equals(13, 13, 1)] = 1;
	state[getIndex_equals(14, 14, 1)] = 1;
	state[getIndex_equals(15, 15, 1)] = 1;
	state[getIndex_equals(16, 16, 1)] = 1;
	state[getIndex_equals(17, 17, 1)] = 1;
	state[getIndex_equals(18, 18, 1)] = 1;
	state[getIndex_equals(19, 19, 1)] = 1;
	state[getIndex_equals(20, 20, 1)] = 1;
	state[getIndex_equals(21, 21, 1)] = 1;
	state[getIndex_equals(22, 22, 1)] = 1;
	state[getIndex_equals(23, 23, 1)] = 1;
	state[getIndex_equals(24, 24, 1)] = 1;
	state[getIndex_equals(25, 25, 1)] = 1;
	state[getIndex_equals(26, 26, 1)] = 1;
	state[getIndex_equals(27, 27, 1)] = 1;
	state[getIndex_equals(28, 28, 1)] = 1;
	state[getIndex_equals(29, 29, 1)] = 1;
	//decision variables
	int actionDecision;
	int index0;
	int index1;
	//main loop
	while(1 == 1){
		//choose action
		actionDecision = nondet_Int();
		switch(actionDecision){
		case 1:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 30){
				pick_up(object[index0]);
			}
			break;
		case 2:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 30){
				put_down(object[index0]);
			}
			break;
		case 3:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 30){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 30){
					stack(object[index0], object[index1]);
				}
			}
			break;
		case 4:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 30){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 30){
					unstack(object[index0], object[index1]);
				}
			}
			break;
		}
		//check if goal state reached
		if(state[getIndex_on(22, 9, 0)] && state[getIndex_on(9, 11, 0)] && state[getIndex_on(11, 10, 0)] && state[getIndex_on(10, 27, 0)] && state[getIndex_on(27, 13, 0)] && state[getIndex_on(13, 21, 0)] && state[getIndex_on(21, 6, 0)] && state[getIndex_on(6, 23, 0)] && state[getIndex_on(23, 8, 0)] && state[getIndex_on(8, 25, 0)] && state[getIndex_on(25, 18, 0)] && state[getIndex_on(18, 17, 0)] && state[getIndex_on(17, 0, 0)] && state[getIndex_on(0, 26, 0)] && state[getIndex_on(26, 5, 0)] && state[getIndex_on(5, 28, 0)] && state[getIndex_on(28, 12, 0)] && state[getIndex_on(12, 24, 0)] && state[getIndex_on(24, 29, 0)] && state[getIndex_on(29, 3, 0)] && state[getIndex_on(3, 20, 0)] && state[getIndex_on(20, 2, 0)] && state[getIndex_on(2, 7, 0)] && state[getIndex_on(7, 4, 0)] && state[getIndex_on(4, 14, 0)] && state[getIndex_on(14, 16, 0)] && state[getIndex_on(16, 15, 0)] && state[getIndex_on(15, 1, 0)] && state[getIndex_on(1, 19, 0)]){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}
