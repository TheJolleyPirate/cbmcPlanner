//PREAMBLE
//action translation:
//pick_up==pick-up
//put_down==put-down
//stack==stack
//unstack==unstack
//END OF PREAMBLE
#include<stdio.h>
#include <stdlib.h>
int nondet_Int();
//problem definition
//state
int n = 5152;
char state[5152];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
//object translation:
//objectNames = {j, d1, y, u, q, l, f1, d, e1, m, v, f, r, a1, m1, z, x, h1, k, e, n, o, s, b1, r1, q1, h, o1, t1, g, j1, p, k1, u1, b, s1, c1, x1, a, w, w1, i1, n1, v1, t, l1, p1, g1, c, i};
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};
//predicates
int on[50][50];
int ontable[50];
int clear[50];
int handempty;
int holding[50];
int equals[50][50];

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
	else{
		exit(-1);
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
	else{
		exit(-1);
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
	else{
		exit(-1);
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
	else{
		exit(-1);
	}
	return;
}
//main loop
int main(){
	//setting on to -1
	for(int i0 = 0; i0 < 50; i0++){
		for(int i1 = 0; i1 < 50; i1++){
			on[i0][i1] = -1;
		}
	}
	//setting ontable to -1
	for(int i0 = 0; i0 < 50; i0++){
		ontable[i0] = -1;
	}
	//setting clear to -1
	for(int i0 = 0; i0 < 50; i0++){
		clear[i0] = -1;
	}
	//setting handempty to -1
	handempty = -1;
	//setting holding to -1
	for(int i0 = 0; i0 < 50; i0++){
		holding[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 50; i0++){
		for(int i1 = 0; i1 < 50; i1++){
			equals[i0][i1] = -1;
		}
	}
	state[getIndex_clear(0, 1)] = 1;
	state[getIndex_clear(1, 1)] = 1;
	state[getIndex_clear(2, 1)] = 1;
	state[getIndex_clear(3, 1)] = 1;
	state[getIndex_clear(4, 1)] = 1;
	state[getIndex_ontable(5, 1)] = 1;
	state[getIndex_ontable(6, 1)] = 1;
	state[getIndex_ontable(7, 1)] = 1;
	state[getIndex_ontable(3, 1)] = 1;
	state[getIndex_ontable(4, 1)] = 1;
	state[getIndex_on(0, 8, 1)] = 1;
	state[getIndex_on(8, 9, 1)] = 1;
	state[getIndex_on(9, 10, 1)] = 1;
	state[getIndex_on(10, 11, 1)] = 1;
	state[getIndex_on(11, 12, 1)] = 1;
	state[getIndex_on(12, 13, 1)] = 1;
	state[getIndex_on(13, 14, 1)] = 1;
	state[getIndex_on(14, 15, 1)] = 1;
	state[getIndex_on(15, 16, 1)] = 1;
	state[getIndex_on(16, 17, 1)] = 1;
	state[getIndex_on(17, 18, 1)] = 1;
	state[getIndex_on(18, 19, 1)] = 1;
	state[getIndex_on(19, 20, 1)] = 1;
	state[getIndex_on(20, 21, 1)] = 1;
	state[getIndex_on(21, 22, 1)] = 1;
	state[getIndex_on(22, 23, 1)] = 1;
	state[getIndex_on(23, 24, 1)] = 1;
	state[getIndex_on(24, 25, 1)] = 1;
	state[getIndex_on(25, 26, 1)] = 1;
	state[getIndex_on(26, 27, 1)] = 1;
	state[getIndex_on(27, 28, 1)] = 1;
	state[getIndex_on(28, 29, 1)] = 1;
	state[getIndex_on(29, 30, 1)] = 1;
	state[getIndex_on(30, 31, 1)] = 1;
	state[getIndex_on(31, 32, 1)] = 1;
	state[getIndex_on(32, 5, 1)] = 1;
	state[getIndex_on(1, 33, 1)] = 1;
	state[getIndex_on(33, 34, 1)] = 1;
	state[getIndex_on(34, 35, 1)] = 1;
	state[getIndex_on(35, 36, 1)] = 1;
	state[getIndex_on(36, 37, 1)] = 1;
	state[getIndex_on(37, 38, 1)] = 1;
	state[getIndex_on(38, 39, 1)] = 1;
	state[getIndex_on(39, 40, 1)] = 1;
	state[getIndex_on(40, 41, 1)] = 1;
	state[getIndex_on(41, 42, 1)] = 1;
	state[getIndex_on(42, 43, 1)] = 1;
	state[getIndex_on(43, 44, 1)] = 1;
	state[getIndex_on(44, 45, 1)] = 1;
	state[getIndex_on(45, 6, 1)] = 1;
	state[getIndex_on(2, 46, 1)] = 1;
	state[getIndex_on(46, 47, 1)] = 1;
	state[getIndex_on(47, 48, 1)] = 1;
	state[getIndex_on(48, 49, 1)] = 1;
	state[getIndex_on(49, 7, 1)] = 1;
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
	state[getIndex_equals(30, 30, 1)] = 1;
	state[getIndex_equals(31, 31, 1)] = 1;
	state[getIndex_equals(32, 32, 1)] = 1;
	state[getIndex_equals(33, 33, 1)] = 1;
	state[getIndex_equals(34, 34, 1)] = 1;
	state[getIndex_equals(35, 35, 1)] = 1;
	state[getIndex_equals(36, 36, 1)] = 1;
	state[getIndex_equals(37, 37, 1)] = 1;
	state[getIndex_equals(38, 38, 1)] = 1;
	state[getIndex_equals(39, 39, 1)] = 1;
	state[getIndex_equals(40, 40, 1)] = 1;
	state[getIndex_equals(41, 41, 1)] = 1;
	state[getIndex_equals(42, 42, 1)] = 1;
	state[getIndex_equals(43, 43, 1)] = 1;
	state[getIndex_equals(44, 44, 1)] = 1;
	state[getIndex_equals(45, 45, 1)] = 1;
	state[getIndex_equals(46, 46, 1)] = 1;
	state[getIndex_equals(47, 47, 1)] = 1;
	state[getIndex_equals(48, 48, 1)] = 1;
	state[getIndex_equals(49, 49, 1)] = 1;
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
			if(index0 >= 0 && index0 < 50){
				pick_up(object[index0]);
			}
			break;
		case 2:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 50){
				put_down(object[index0]);
			}
			break;
		case 3:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 50){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 50){
					stack(object[index0], object[index1]);
				}
			}
			break;
		case 4:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 50){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 50){
					unstack(object[index0], object[index1]);
				}
			}
			break;
		}
		//check if goal state reached
		if(state[getIndex_on(48, 38, 0)] && state[getIndex_on(38, 33, 0)] && state[getIndex_on(33, 20, 0)] && state[getIndex_on(20, 14, 0)] && state[getIndex_on(14, 37, 0)] && state[getIndex_on(37, 18, 0)] && state[getIndex_on(18, 17, 0)] && state[getIndex_on(17, 28, 0)] && state[getIndex_on(28, 10, 0)] && state[getIndex_on(10, 19, 0)] && state[getIndex_on(19, 4, 0)] && state[getIndex_on(4, 24, 0)] && state[getIndex_on(24, 22, 0)] && state[getIndex_on(22, 45, 0)] && state[getIndex_on(45, 41, 0)] && state[getIndex_on(41, 1, 0)] && state[getIndex_on(1, 39, 0)] && state[getIndex_on(39, 9, 0)] && state[getIndex_on(9, 12, 0)] && state[getIndex_on(12, 29, 0)] && state[getIndex_on(29, 35, 0)] && state[getIndex_on(35, 2, 0)] && state[getIndex_on(2, 42, 0)] && state[getIndex_on(42, 34, 0)] && state[getIndex_on(34, 26, 0)] && state[getIndex_on(26, 8, 0)] && state[getIndex_on(8, 6, 0)] && state[getIndex_on(6, 31, 0)] && state[getIndex_on(31, 11, 0)] && state[getIndex_on(11, 7, 0)] && state[getIndex_on(7, 36, 0)] && state[getIndex_on(36, 13, 0)] && state[getIndex_on(13, 21, 0)] && state[getIndex_on(21, 3, 0)] && state[getIndex_on(3, 5, 0)] && state[getIndex_on(5, 23, 0)] && state[getIndex_on(23, 43, 0)] && state[getIndex_on(43, 40, 0)] && state[getIndex_on(40, 32, 0)] && state[getIndex_on(32, 49, 0)] && state[getIndex_on(49, 27, 0)] && state[getIndex_on(27, 16, 0)] && state[getIndex_on(16, 0, 0)] && state[getIndex_on(0, 30, 0)] && state[getIndex_on(30, 44, 0)] && state[getIndex_on(44, 47, 0)] && state[getIndex_on(47, 15, 0)] && state[getIndex_on(15, 46, 0)] && state[getIndex_on(46, 25, 0)]){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}
