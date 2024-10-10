//PREAMBLE
//action translation:
//board==board
//depart==depart
//up==up
//down==down
//END OF PREAMBLE
#include<stdio.h>
#include <stdlib.h>
int nondet_Int();
//problem definition
//state
int n = 148;
char state[148];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
//predicates
int origin[9][9];
int floor[9];
int passenger[9];
int destin[9][9];
int above[9][9];
int boarded[9];
int served[9];
int lift_at[9];
int equals[9][9];

//get index functions
int getIndex_origin(int x0, int x1, int set){
	int index;
	if(origin[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			origin[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = origin[x0][x1];
	}
	return index;
}
int getIndex_floor(int x0, int set){
	int index;
	if(floor[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			floor[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = floor[x0];
	}
	return index;
}
int getIndex_passenger(int x0, int set){
	int index;
	if(passenger[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			passenger[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = passenger[x0];
	}
	return index;
}
int getIndex_destin(int x0, int x1, int set){
	int index;
	if(destin[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			destin[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = destin[x0][x1];
	}
	return index;
}
int getIndex_above(int x0, int x1, int set){
	int index;
	if(above[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			above[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = above[x0][x1];
	}
	return index;
}
int getIndex_boarded(int x0, int set){
	int index;
	if(boarded[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			boarded[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = boarded[x0];
	}
	return index;
}
int getIndex_served(int x0, int set){
	int index;
	if(served[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			served[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = served[x0];
	}
	return index;
}
int getIndex_lift_at(int x0, int set){
	int index;
	if(lift_at[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			lift_at[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = lift_at[x0];
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
void board(int f, int p){
	if((state[getIndex_floor(f, 0)] && state[getIndex_passenger(p, 0)] && state[getIndex_lift_at(f, 0)] && state[getIndex_origin(p, f, 0)])){
		state[getIndex_boarded(p, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void depart(int f, int p){
	if((state[getIndex_floor(f, 0)] && state[getIndex_passenger(p, 0)] && state[getIndex_lift_at(f, 0)] && state[getIndex_destin(p, f, 0)] && state[getIndex_boarded(p, 0)])){
		state[getIndex_boarded(p, 1)] = 0;
		state[getIndex_served(p, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void up(int f1, int f2){
	if((state[getIndex_floor(f1, 0)] && state[getIndex_floor(f2, 0)] && state[getIndex_lift_at(f1, 0)] && state[getIndex_above(f1, f2, 0)])){
		state[getIndex_lift_at(f1, 1)] = 0;
		state[getIndex_lift_at(f2, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void down(int f1, int f2){
	if((state[getIndex_floor(f1, 0)] && state[getIndex_floor(f2, 0)] && state[getIndex_lift_at(f1, 0)] && state[getIndex_above(f2, f1, 0)])){
		state[getIndex_lift_at(f1, 1)] = 0;
		state[getIndex_lift_at(f2, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
//main loop
int main(){
	//setting origin to -1
	for(int i0 = 0; i0 < 9; i0++){
		for(int i1 = 0; i1 < 9; i1++){
			origin[i0][i1] = -1;
		}
	}
	//setting floor to -1
	for(int i0 = 0; i0 < 9; i0++){
		floor[i0] = -1;
	}
	//setting passenger to -1
	for(int i0 = 0; i0 < 9; i0++){
		passenger[i0] = -1;
	}
	//setting destin to -1
	for(int i0 = 0; i0 < 9; i0++){
		for(int i1 = 0; i1 < 9; i1++){
			destin[i0][i1] = -1;
		}
	}
	//setting above to -1
	for(int i0 = 0; i0 < 9; i0++){
		for(int i1 = 0; i1 < 9; i1++){
			above[i0][i1] = -1;
		}
	}
	//setting boarded to -1
	for(int i0 = 0; i0 < 9; i0++){
		boarded[i0] = -1;
	}
	//setting served to -1
	for(int i0 = 0; i0 < 9; i0++){
		served[i0] = -1;
	}
	//setting lift_at to -1
	for(int i0 = 0; i0 < 9; i0++){
		lift_at[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 9; i0++){
		for(int i1 = 0; i1 < 9; i1++){
			equals[i0][i1] = -1;
		}
	}
	state[getIndex_passenger(0, 1)] = 1;
	state[getIndex_passenger(1, 1)] = 1;
	state[getIndex_passenger(2, 1)] = 1;
	state[getIndex_floor(3, 1)] = 1;
	state[getIndex_floor(4, 1)] = 1;
	state[getIndex_floor(5, 1)] = 1;
	state[getIndex_floor(6, 1)] = 1;
	state[getIndex_floor(7, 1)] = 1;
	state[getIndex_floor(8, 1)] = 1;
	state[getIndex_above(3, 4, 1)] = 1;
	state[getIndex_above(3, 5, 1)] = 1;
	state[getIndex_above(3, 6, 1)] = 1;
	state[getIndex_above(3, 7, 1)] = 1;
	state[getIndex_above(3, 8, 1)] = 1;
	state[getIndex_above(4, 5, 1)] = 1;
	state[getIndex_above(4, 6, 1)] = 1;
	state[getIndex_above(4, 7, 1)] = 1;
	state[getIndex_above(4, 8, 1)] = 1;
	state[getIndex_above(5, 6, 1)] = 1;
	state[getIndex_above(5, 7, 1)] = 1;
	state[getIndex_above(5, 8, 1)] = 1;
	state[getIndex_above(6, 7, 1)] = 1;
	state[getIndex_above(6, 8, 1)] = 1;
	state[getIndex_above(7, 8, 1)] = 1;
	state[getIndex_origin(0, 4, 1)] = 1;
	state[getIndex_destin(0, 3, 1)] = 1;
	state[getIndex_origin(1, 7, 1)] = 1;
	state[getIndex_destin(1, 3, 1)] = 1;
	state[getIndex_origin(2, 6, 1)] = 1;
	state[getIndex_destin(2, 3, 1)] = 1;
	state[getIndex_lift_at(3, 1)] = 1;
	state[getIndex_equals(0, 0, 1)] = 1;
	state[getIndex_equals(1, 1, 1)] = 1;
	state[getIndex_equals(2, 2, 1)] = 1;
	state[getIndex_equals(3, 3, 1)] = 1;
	state[getIndex_equals(4, 4, 1)] = 1;
	state[getIndex_equals(5, 5, 1)] = 1;
	state[getIndex_equals(6, 6, 1)] = 1;
	state[getIndex_equals(7, 7, 1)] = 1;
	state[getIndex_equals(8, 8, 1)] = 1;
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
			if(index0 >= 0 && index0 < 9){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 9){
					board(object[index0], object[index1]);
				}
			}
			break;
		case 2:
			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 9){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 9){
					depart(object[index0], object[index1]);
				}
			}
			break;
		case 3:
			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 9){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 9){
					up(object[index0], object[index1]);
				}
			}
			break;
		case 4:
			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 9){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 9){
					down(object[index0], object[index1]);
				}
			}
			break;
		}
		//check if goal state reached
		if((state[getIndex_served(0, 0)] && state[getIndex_served(1, 0)] && state[getIndex_served(2, 0)])){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}
