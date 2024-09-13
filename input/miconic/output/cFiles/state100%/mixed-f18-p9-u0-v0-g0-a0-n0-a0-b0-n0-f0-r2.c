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
int n = 3052;
char state[3052];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
//object translation:
//objectNames = {p0, p1, p2, p3, p4, p5, p6, p7, p8, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17};
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
//predicates
int origin[27][27];
int floor[27];
int passenger[27];
int destin[27][27];
int above[27][27];
int boarded[27];
int served[27];
int lift_at[27];
int equals[27][27];

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
	for(int i0 = 0; i0 < 27; i0++){
		for(int i1 = 0; i1 < 27; i1++){
			origin[i0][i1] = -1;
		}
	}
	//setting floor to -1
	for(int i0 = 0; i0 < 27; i0++){
		floor[i0] = -1;
	}
	//setting passenger to -1
	for(int i0 = 0; i0 < 27; i0++){
		passenger[i0] = -1;
	}
	//setting destin to -1
	for(int i0 = 0; i0 < 27; i0++){
		for(int i1 = 0; i1 < 27; i1++){
			destin[i0][i1] = -1;
		}
	}
	//setting above to -1
	for(int i0 = 0; i0 < 27; i0++){
		for(int i1 = 0; i1 < 27; i1++){
			above[i0][i1] = -1;
		}
	}
	//setting boarded to -1
	for(int i0 = 0; i0 < 27; i0++){
		boarded[i0] = -1;
	}
	//setting served to -1
	for(int i0 = 0; i0 < 27; i0++){
		served[i0] = -1;
	}
	//setting lift_at to -1
	for(int i0 = 0; i0 < 27; i0++){
		lift_at[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 27; i0++){
		for(int i1 = 0; i1 < 27; i1++){
			equals[i0][i1] = -1;
		}
	}
	state[getIndex_passenger(0, 1)] = 1;
	state[getIndex_passenger(1, 1)] = 1;
	state[getIndex_passenger(2, 1)] = 1;
	state[getIndex_passenger(3, 1)] = 1;
	state[getIndex_passenger(4, 1)] = 1;
	state[getIndex_passenger(5, 1)] = 1;
	state[getIndex_passenger(6, 1)] = 1;
	state[getIndex_passenger(7, 1)] = 1;
	state[getIndex_passenger(8, 1)] = 1;
	state[getIndex_floor(9, 1)] = 1;
	state[getIndex_floor(10, 1)] = 1;
	state[getIndex_floor(11, 1)] = 1;
	state[getIndex_floor(12, 1)] = 1;
	state[getIndex_floor(13, 1)] = 1;
	state[getIndex_floor(14, 1)] = 1;
	state[getIndex_floor(15, 1)] = 1;
	state[getIndex_floor(16, 1)] = 1;
	state[getIndex_floor(17, 1)] = 1;
	state[getIndex_floor(18, 1)] = 1;
	state[getIndex_floor(19, 1)] = 1;
	state[getIndex_floor(20, 1)] = 1;
	state[getIndex_floor(21, 1)] = 1;
	state[getIndex_floor(22, 1)] = 1;
	state[getIndex_floor(23, 1)] = 1;
	state[getIndex_floor(24, 1)] = 1;
	state[getIndex_floor(25, 1)] = 1;
	state[getIndex_floor(26, 1)] = 1;
	state[getIndex_above(9, 10, 1)] = 1;
	state[getIndex_above(9, 11, 1)] = 1;
	state[getIndex_above(9, 12, 1)] = 1;
	state[getIndex_above(9, 13, 1)] = 1;
	state[getIndex_above(9, 14, 1)] = 1;
	state[getIndex_above(9, 15, 1)] = 1;
	state[getIndex_above(9, 16, 1)] = 1;
	state[getIndex_above(9, 17, 1)] = 1;
	state[getIndex_above(9, 18, 1)] = 1;
	state[getIndex_above(9, 19, 1)] = 1;
	state[getIndex_above(9, 20, 1)] = 1;
	state[getIndex_above(9, 21, 1)] = 1;
	state[getIndex_above(9, 22, 1)] = 1;
	state[getIndex_above(9, 23, 1)] = 1;
	state[getIndex_above(9, 24, 1)] = 1;
	state[getIndex_above(9, 25, 1)] = 1;
	state[getIndex_above(9, 26, 1)] = 1;
	state[getIndex_above(10, 11, 1)] = 1;
	state[getIndex_above(10, 12, 1)] = 1;
	state[getIndex_above(10, 13, 1)] = 1;
	state[getIndex_above(10, 14, 1)] = 1;
	state[getIndex_above(10, 15, 1)] = 1;
	state[getIndex_above(10, 16, 1)] = 1;
	state[getIndex_above(10, 17, 1)] = 1;
	state[getIndex_above(10, 18, 1)] = 1;
	state[getIndex_above(10, 19, 1)] = 1;
	state[getIndex_above(10, 20, 1)] = 1;
	state[getIndex_above(10, 21, 1)] = 1;
	state[getIndex_above(10, 22, 1)] = 1;
	state[getIndex_above(10, 23, 1)] = 1;
	state[getIndex_above(10, 24, 1)] = 1;
	state[getIndex_above(10, 25, 1)] = 1;
	state[getIndex_above(10, 26, 1)] = 1;
	state[getIndex_above(11, 12, 1)] = 1;
	state[getIndex_above(11, 13, 1)] = 1;
	state[getIndex_above(11, 14, 1)] = 1;
	state[getIndex_above(11, 15, 1)] = 1;
	state[getIndex_above(11, 16, 1)] = 1;
	state[getIndex_above(11, 17, 1)] = 1;
	state[getIndex_above(11, 18, 1)] = 1;
	state[getIndex_above(11, 19, 1)] = 1;
	state[getIndex_above(11, 20, 1)] = 1;
	state[getIndex_above(11, 21, 1)] = 1;
	state[getIndex_above(11, 22, 1)] = 1;
	state[getIndex_above(11, 23, 1)] = 1;
	state[getIndex_above(11, 24, 1)] = 1;
	state[getIndex_above(11, 25, 1)] = 1;
	state[getIndex_above(11, 26, 1)] = 1;
	state[getIndex_above(12, 13, 1)] = 1;
	state[getIndex_above(12, 14, 1)] = 1;
	state[getIndex_above(12, 15, 1)] = 1;
	state[getIndex_above(12, 16, 1)] = 1;
	state[getIndex_above(12, 17, 1)] = 1;
	state[getIndex_above(12, 18, 1)] = 1;
	state[getIndex_above(12, 19, 1)] = 1;
	state[getIndex_above(12, 20, 1)] = 1;
	state[getIndex_above(12, 21, 1)] = 1;
	state[getIndex_above(12, 22, 1)] = 1;
	state[getIndex_above(12, 23, 1)] = 1;
	state[getIndex_above(12, 24, 1)] = 1;
	state[getIndex_above(12, 25, 1)] = 1;
	state[getIndex_above(12, 26, 1)] = 1;
	state[getIndex_above(13, 14, 1)] = 1;
	state[getIndex_above(13, 15, 1)] = 1;
	state[getIndex_above(13, 16, 1)] = 1;
	state[getIndex_above(13, 17, 1)] = 1;
	state[getIndex_above(13, 18, 1)] = 1;
	state[getIndex_above(13, 19, 1)] = 1;
	state[getIndex_above(13, 20, 1)] = 1;
	state[getIndex_above(13, 21, 1)] = 1;
	state[getIndex_above(13, 22, 1)] = 1;
	state[getIndex_above(13, 23, 1)] = 1;
	state[getIndex_above(13, 24, 1)] = 1;
	state[getIndex_above(13, 25, 1)] = 1;
	state[getIndex_above(13, 26, 1)] = 1;
	state[getIndex_above(14, 15, 1)] = 1;
	state[getIndex_above(14, 16, 1)] = 1;
	state[getIndex_above(14, 17, 1)] = 1;
	state[getIndex_above(14, 18, 1)] = 1;
	state[getIndex_above(14, 19, 1)] = 1;
	state[getIndex_above(14, 20, 1)] = 1;
	state[getIndex_above(14, 21, 1)] = 1;
	state[getIndex_above(14, 22, 1)] = 1;
	state[getIndex_above(14, 23, 1)] = 1;
	state[getIndex_above(14, 24, 1)] = 1;
	state[getIndex_above(14, 25, 1)] = 1;
	state[getIndex_above(14, 26, 1)] = 1;
	state[getIndex_above(15, 16, 1)] = 1;
	state[getIndex_above(15, 17, 1)] = 1;
	state[getIndex_above(15, 18, 1)] = 1;
	state[getIndex_above(15, 19, 1)] = 1;
	state[getIndex_above(15, 20, 1)] = 1;
	state[getIndex_above(15, 21, 1)] = 1;
	state[getIndex_above(15, 22, 1)] = 1;
	state[getIndex_above(15, 23, 1)] = 1;
	state[getIndex_above(15, 24, 1)] = 1;
	state[getIndex_above(15, 25, 1)] = 1;
	state[getIndex_above(15, 26, 1)] = 1;
	state[getIndex_above(16, 17, 1)] = 1;
	state[getIndex_above(16, 18, 1)] = 1;
	state[getIndex_above(16, 19, 1)] = 1;
	state[getIndex_above(16, 20, 1)] = 1;
	state[getIndex_above(16, 21, 1)] = 1;
	state[getIndex_above(16, 22, 1)] = 1;
	state[getIndex_above(16, 23, 1)] = 1;
	state[getIndex_above(16, 24, 1)] = 1;
	state[getIndex_above(16, 25, 1)] = 1;
	state[getIndex_above(16, 26, 1)] = 1;
	state[getIndex_above(17, 18, 1)] = 1;
	state[getIndex_above(17, 19, 1)] = 1;
	state[getIndex_above(17, 20, 1)] = 1;
	state[getIndex_above(17, 21, 1)] = 1;
	state[getIndex_above(17, 22, 1)] = 1;
	state[getIndex_above(17, 23, 1)] = 1;
	state[getIndex_above(17, 24, 1)] = 1;
	state[getIndex_above(17, 25, 1)] = 1;
	state[getIndex_above(17, 26, 1)] = 1;
	state[getIndex_above(18, 19, 1)] = 1;
	state[getIndex_above(18, 20, 1)] = 1;
	state[getIndex_above(18, 21, 1)] = 1;
	state[getIndex_above(18, 22, 1)] = 1;
	state[getIndex_above(18, 23, 1)] = 1;
	state[getIndex_above(18, 24, 1)] = 1;
	state[getIndex_above(18, 25, 1)] = 1;
	state[getIndex_above(18, 26, 1)] = 1;
	state[getIndex_above(19, 20, 1)] = 1;
	state[getIndex_above(19, 21, 1)] = 1;
	state[getIndex_above(19, 22, 1)] = 1;
	state[getIndex_above(19, 23, 1)] = 1;
	state[getIndex_above(19, 24, 1)] = 1;
	state[getIndex_above(19, 25, 1)] = 1;
	state[getIndex_above(19, 26, 1)] = 1;
	state[getIndex_above(20, 21, 1)] = 1;
	state[getIndex_above(20, 22, 1)] = 1;
	state[getIndex_above(20, 23, 1)] = 1;
	state[getIndex_above(20, 24, 1)] = 1;
	state[getIndex_above(20, 25, 1)] = 1;
	state[getIndex_above(20, 26, 1)] = 1;
	state[getIndex_above(21, 22, 1)] = 1;
	state[getIndex_above(21, 23, 1)] = 1;
	state[getIndex_above(21, 24, 1)] = 1;
	state[getIndex_above(21, 25, 1)] = 1;
	state[getIndex_above(21, 26, 1)] = 1;
	state[getIndex_above(22, 23, 1)] = 1;
	state[getIndex_above(22, 24, 1)] = 1;
	state[getIndex_above(22, 25, 1)] = 1;
	state[getIndex_above(22, 26, 1)] = 1;
	state[getIndex_above(23, 24, 1)] = 1;
	state[getIndex_above(23, 25, 1)] = 1;
	state[getIndex_above(23, 26, 1)] = 1;
	state[getIndex_above(24, 25, 1)] = 1;
	state[getIndex_above(24, 26, 1)] = 1;
	state[getIndex_above(25, 26, 1)] = 1;
	state[getIndex_origin(0, 22, 1)] = 1;
	state[getIndex_destin(0, 21, 1)] = 1;
	state[getIndex_origin(1, 25, 1)] = 1;
	state[getIndex_destin(1, 9, 1)] = 1;
	state[getIndex_origin(2, 12, 1)] = 1;
	state[getIndex_destin(2, 21, 1)] = 1;
	state[getIndex_origin(3, 11, 1)] = 1;
	state[getIndex_destin(3, 23, 1)] = 1;
	state[getIndex_origin(4, 16, 1)] = 1;
	state[getIndex_destin(4, 12, 1)] = 1;
	state[getIndex_origin(5, 17, 1)] = 1;
	state[getIndex_destin(5, 14, 1)] = 1;
	state[getIndex_origin(6, 22, 1)] = 1;
	state[getIndex_destin(6, 17, 1)] = 1;
	state[getIndex_origin(7, 9, 1)] = 1;
	state[getIndex_destin(7, 21, 1)] = 1;
	state[getIndex_origin(8, 10, 1)] = 1;
	state[getIndex_destin(8, 18, 1)] = 1;
	state[getIndex_lift_at(9, 1)] = 1;
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
			if(index0 >= 0 && index0 < 27){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 27){
					board(object[index0], object[index1]);
				}
			}
			break;
		case 2:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 27){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 27){
					depart(object[index0], object[index1]);
				}
			}
			break;
		case 3:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 27){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 27){
					up(object[index0], object[index1]);
				}
			}
			break;
		case 4:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 27){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 27){
					down(object[index0], object[index1]);
				}
			}
			break;
		}
		//check if goal state reached
		if((state[getIndex_served(0, 0)] && state[getIndex_served(1, 0)] && state[getIndex_served(2, 0)] && state[getIndex_served(3, 0)] && state[getIndex_served(4, 0)] && state[getIndex_served(5, 0)] && state[getIndex_served(6, 0)] && state[getIndex_served(7, 0)] && state[getIndex_served(8, 0)])){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}
