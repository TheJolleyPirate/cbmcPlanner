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
int n = 8326;
char state[8326];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
//object translation:
//objectNames = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29};
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};
//predicates
int origin[45][45];
int floor[45];
int passenger[45];
int destin[45][45];
int above[45][45];
int boarded[45];
int served[45];
int lift_at[45];
int equals[45][45];

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
	for(int i0 = 0; i0 < 45; i0++){
		for(int i1 = 0; i1 < 45; i1++){
			origin[i0][i1] = -1;
		}
	}
	//setting floor to -1
	for(int i0 = 0; i0 < 45; i0++){
		floor[i0] = -1;
	}
	//setting passenger to -1
	for(int i0 = 0; i0 < 45; i0++){
		passenger[i0] = -1;
	}
	//setting destin to -1
	for(int i0 = 0; i0 < 45; i0++){
		for(int i1 = 0; i1 < 45; i1++){
			destin[i0][i1] = -1;
		}
	}
	//setting above to -1
	for(int i0 = 0; i0 < 45; i0++){
		for(int i1 = 0; i1 < 45; i1++){
			above[i0][i1] = -1;
		}
	}
	//setting boarded to -1
	for(int i0 = 0; i0 < 45; i0++){
		boarded[i0] = -1;
	}
	//setting served to -1
	for(int i0 = 0; i0 < 45; i0++){
		served[i0] = -1;
	}
	//setting lift_at to -1
	for(int i0 = 0; i0 < 45; i0++){
		lift_at[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 45; i0++){
		for(int i1 = 0; i1 < 45; i1++){
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
	state[getIndex_passenger(9, 1)] = 1;
	state[getIndex_passenger(10, 1)] = 1;
	state[getIndex_passenger(11, 1)] = 1;
	state[getIndex_passenger(12, 1)] = 1;
	state[getIndex_passenger(13, 1)] = 1;
	state[getIndex_passenger(14, 1)] = 1;
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
	state[getIndex_floor(27, 1)] = 1;
	state[getIndex_floor(28, 1)] = 1;
	state[getIndex_floor(29, 1)] = 1;
	state[getIndex_floor(30, 1)] = 1;
	state[getIndex_floor(31, 1)] = 1;
	state[getIndex_floor(32, 1)] = 1;
	state[getIndex_floor(33, 1)] = 1;
	state[getIndex_floor(34, 1)] = 1;
	state[getIndex_floor(35, 1)] = 1;
	state[getIndex_floor(36, 1)] = 1;
	state[getIndex_floor(37, 1)] = 1;
	state[getIndex_floor(38, 1)] = 1;
	state[getIndex_floor(39, 1)] = 1;
	state[getIndex_floor(40, 1)] = 1;
	state[getIndex_floor(41, 1)] = 1;
	state[getIndex_floor(42, 1)] = 1;
	state[getIndex_floor(43, 1)] = 1;
	state[getIndex_floor(44, 1)] = 1;
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
	state[getIndex_above(15, 27, 1)] = 1;
	state[getIndex_above(15, 28, 1)] = 1;
	state[getIndex_above(15, 29, 1)] = 1;
	state[getIndex_above(15, 30, 1)] = 1;
	state[getIndex_above(15, 31, 1)] = 1;
	state[getIndex_above(15, 32, 1)] = 1;
	state[getIndex_above(15, 33, 1)] = 1;
	state[getIndex_above(15, 34, 1)] = 1;
	state[getIndex_above(15, 35, 1)] = 1;
	state[getIndex_above(15, 36, 1)] = 1;
	state[getIndex_above(15, 37, 1)] = 1;
	state[getIndex_above(15, 38, 1)] = 1;
	state[getIndex_above(15, 39, 1)] = 1;
	state[getIndex_above(15, 40, 1)] = 1;
	state[getIndex_above(15, 41, 1)] = 1;
	state[getIndex_above(15, 42, 1)] = 1;
	state[getIndex_above(15, 43, 1)] = 1;
	state[getIndex_above(15, 44, 1)] = 1;
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
	state[getIndex_above(16, 27, 1)] = 1;
	state[getIndex_above(16, 28, 1)] = 1;
	state[getIndex_above(16, 29, 1)] = 1;
	state[getIndex_above(16, 30, 1)] = 1;
	state[getIndex_above(16, 31, 1)] = 1;
	state[getIndex_above(16, 32, 1)] = 1;
	state[getIndex_above(16, 33, 1)] = 1;
	state[getIndex_above(16, 34, 1)] = 1;
	state[getIndex_above(16, 35, 1)] = 1;
	state[getIndex_above(16, 36, 1)] = 1;
	state[getIndex_above(16, 37, 1)] = 1;
	state[getIndex_above(16, 38, 1)] = 1;
	state[getIndex_above(16, 39, 1)] = 1;
	state[getIndex_above(16, 40, 1)] = 1;
	state[getIndex_above(16, 41, 1)] = 1;
	state[getIndex_above(16, 42, 1)] = 1;
	state[getIndex_above(16, 43, 1)] = 1;
	state[getIndex_above(16, 44, 1)] = 1;
	state[getIndex_above(17, 18, 1)] = 1;
	state[getIndex_above(17, 19, 1)] = 1;
	state[getIndex_above(17, 20, 1)] = 1;
	state[getIndex_above(17, 21, 1)] = 1;
	state[getIndex_above(17, 22, 1)] = 1;
	state[getIndex_above(17, 23, 1)] = 1;
	state[getIndex_above(17, 24, 1)] = 1;
	state[getIndex_above(17, 25, 1)] = 1;
	state[getIndex_above(17, 26, 1)] = 1;
	state[getIndex_above(17, 27, 1)] = 1;
	state[getIndex_above(17, 28, 1)] = 1;
	state[getIndex_above(17, 29, 1)] = 1;
	state[getIndex_above(17, 30, 1)] = 1;
	state[getIndex_above(17, 31, 1)] = 1;
	state[getIndex_above(17, 32, 1)] = 1;
	state[getIndex_above(17, 33, 1)] = 1;
	state[getIndex_above(17, 34, 1)] = 1;
	state[getIndex_above(17, 35, 1)] = 1;
	state[getIndex_above(17, 36, 1)] = 1;
	state[getIndex_above(17, 37, 1)] = 1;
	state[getIndex_above(17, 38, 1)] = 1;
	state[getIndex_above(17, 39, 1)] = 1;
	state[getIndex_above(17, 40, 1)] = 1;
	state[getIndex_above(17, 41, 1)] = 1;
	state[getIndex_above(17, 42, 1)] = 1;
	state[getIndex_above(17, 43, 1)] = 1;
	state[getIndex_above(17, 44, 1)] = 1;
	state[getIndex_above(18, 19, 1)] = 1;
	state[getIndex_above(18, 20, 1)] = 1;
	state[getIndex_above(18, 21, 1)] = 1;
	state[getIndex_above(18, 22, 1)] = 1;
	state[getIndex_above(18, 23, 1)] = 1;
	state[getIndex_above(18, 24, 1)] = 1;
	state[getIndex_above(18, 25, 1)] = 1;
	state[getIndex_above(18, 26, 1)] = 1;
	state[getIndex_above(18, 27, 1)] = 1;
	state[getIndex_above(18, 28, 1)] = 1;
	state[getIndex_above(18, 29, 1)] = 1;
	state[getIndex_above(18, 30, 1)] = 1;
	state[getIndex_above(18, 31, 1)] = 1;
	state[getIndex_above(18, 32, 1)] = 1;
	state[getIndex_above(18, 33, 1)] = 1;
	state[getIndex_above(18, 34, 1)] = 1;
	state[getIndex_above(18, 35, 1)] = 1;
	state[getIndex_above(18, 36, 1)] = 1;
	state[getIndex_above(18, 37, 1)] = 1;
	state[getIndex_above(18, 38, 1)] = 1;
	state[getIndex_above(18, 39, 1)] = 1;
	state[getIndex_above(18, 40, 1)] = 1;
	state[getIndex_above(18, 41, 1)] = 1;
	state[getIndex_above(18, 42, 1)] = 1;
	state[getIndex_above(18, 43, 1)] = 1;
	state[getIndex_above(18, 44, 1)] = 1;
	state[getIndex_above(19, 20, 1)] = 1;
	state[getIndex_above(19, 21, 1)] = 1;
	state[getIndex_above(19, 22, 1)] = 1;
	state[getIndex_above(19, 23, 1)] = 1;
	state[getIndex_above(19, 24, 1)] = 1;
	state[getIndex_above(19, 25, 1)] = 1;
	state[getIndex_above(19, 26, 1)] = 1;
	state[getIndex_above(19, 27, 1)] = 1;
	state[getIndex_above(19, 28, 1)] = 1;
	state[getIndex_above(19, 29, 1)] = 1;
	state[getIndex_above(19, 30, 1)] = 1;
	state[getIndex_above(19, 31, 1)] = 1;
	state[getIndex_above(19, 32, 1)] = 1;
	state[getIndex_above(19, 33, 1)] = 1;
	state[getIndex_above(19, 34, 1)] = 1;
	state[getIndex_above(19, 35, 1)] = 1;
	state[getIndex_above(19, 36, 1)] = 1;
	state[getIndex_above(19, 37, 1)] = 1;
	state[getIndex_above(19, 38, 1)] = 1;
	state[getIndex_above(19, 39, 1)] = 1;
	state[getIndex_above(19, 40, 1)] = 1;
	state[getIndex_above(19, 41, 1)] = 1;
	state[getIndex_above(19, 42, 1)] = 1;
	state[getIndex_above(19, 43, 1)] = 1;
	state[getIndex_above(19, 44, 1)] = 1;
	state[getIndex_above(20, 21, 1)] = 1;
	state[getIndex_above(20, 22, 1)] = 1;
	state[getIndex_above(20, 23, 1)] = 1;
	state[getIndex_above(20, 24, 1)] = 1;
	state[getIndex_above(20, 25, 1)] = 1;
	state[getIndex_above(20, 26, 1)] = 1;
	state[getIndex_above(20, 27, 1)] = 1;
	state[getIndex_above(20, 28, 1)] = 1;
	state[getIndex_above(20, 29, 1)] = 1;
	state[getIndex_above(20, 30, 1)] = 1;
	state[getIndex_above(20, 31, 1)] = 1;
	state[getIndex_above(20, 32, 1)] = 1;
	state[getIndex_above(20, 33, 1)] = 1;
	state[getIndex_above(20, 34, 1)] = 1;
	state[getIndex_above(20, 35, 1)] = 1;
	state[getIndex_above(20, 36, 1)] = 1;
	state[getIndex_above(20, 37, 1)] = 1;
	state[getIndex_above(20, 38, 1)] = 1;
	state[getIndex_above(20, 39, 1)] = 1;
	state[getIndex_above(20, 40, 1)] = 1;
	state[getIndex_above(20, 41, 1)] = 1;
	state[getIndex_above(20, 42, 1)] = 1;
	state[getIndex_above(20, 43, 1)] = 1;
	state[getIndex_above(20, 44, 1)] = 1;
	state[getIndex_above(21, 22, 1)] = 1;
	state[getIndex_above(21, 23, 1)] = 1;
	state[getIndex_above(21, 24, 1)] = 1;
	state[getIndex_above(21, 25, 1)] = 1;
	state[getIndex_above(21, 26, 1)] = 1;
	state[getIndex_above(21, 27, 1)] = 1;
	state[getIndex_above(21, 28, 1)] = 1;
	state[getIndex_above(21, 29, 1)] = 1;
	state[getIndex_above(21, 30, 1)] = 1;
	state[getIndex_above(21, 31, 1)] = 1;
	state[getIndex_above(21, 32, 1)] = 1;
	state[getIndex_above(21, 33, 1)] = 1;
	state[getIndex_above(21, 34, 1)] = 1;
	state[getIndex_above(21, 35, 1)] = 1;
	state[getIndex_above(21, 36, 1)] = 1;
	state[getIndex_above(21, 37, 1)] = 1;
	state[getIndex_above(21, 38, 1)] = 1;
	state[getIndex_above(21, 39, 1)] = 1;
	state[getIndex_above(21, 40, 1)] = 1;
	state[getIndex_above(21, 41, 1)] = 1;
	state[getIndex_above(21, 42, 1)] = 1;
	state[getIndex_above(21, 43, 1)] = 1;
	state[getIndex_above(21, 44, 1)] = 1;
	state[getIndex_above(22, 23, 1)] = 1;
	state[getIndex_above(22, 24, 1)] = 1;
	state[getIndex_above(22, 25, 1)] = 1;
	state[getIndex_above(22, 26, 1)] = 1;
	state[getIndex_above(22, 27, 1)] = 1;
	state[getIndex_above(22, 28, 1)] = 1;
	state[getIndex_above(22, 29, 1)] = 1;
	state[getIndex_above(22, 30, 1)] = 1;
	state[getIndex_above(22, 31, 1)] = 1;
	state[getIndex_above(22, 32, 1)] = 1;
	state[getIndex_above(22, 33, 1)] = 1;
	state[getIndex_above(22, 34, 1)] = 1;
	state[getIndex_above(22, 35, 1)] = 1;
	state[getIndex_above(22, 36, 1)] = 1;
	state[getIndex_above(22, 37, 1)] = 1;
	state[getIndex_above(22, 38, 1)] = 1;
	state[getIndex_above(22, 39, 1)] = 1;
	state[getIndex_above(22, 40, 1)] = 1;
	state[getIndex_above(22, 41, 1)] = 1;
	state[getIndex_above(22, 42, 1)] = 1;
	state[getIndex_above(22, 43, 1)] = 1;
	state[getIndex_above(22, 44, 1)] = 1;
	state[getIndex_above(23, 24, 1)] = 1;
	state[getIndex_above(23, 25, 1)] = 1;
	state[getIndex_above(23, 26, 1)] = 1;
	state[getIndex_above(23, 27, 1)] = 1;
	state[getIndex_above(23, 28, 1)] = 1;
	state[getIndex_above(23, 29, 1)] = 1;
	state[getIndex_above(23, 30, 1)] = 1;
	state[getIndex_above(23, 31, 1)] = 1;
	state[getIndex_above(23, 32, 1)] = 1;
	state[getIndex_above(23, 33, 1)] = 1;
	state[getIndex_above(23, 34, 1)] = 1;
	state[getIndex_above(23, 35, 1)] = 1;
	state[getIndex_above(23, 36, 1)] = 1;
	state[getIndex_above(23, 37, 1)] = 1;
	state[getIndex_above(23, 38, 1)] = 1;
	state[getIndex_above(23, 39, 1)] = 1;
	state[getIndex_above(23, 40, 1)] = 1;
	state[getIndex_above(23, 41, 1)] = 1;
	state[getIndex_above(23, 42, 1)] = 1;
	state[getIndex_above(23, 43, 1)] = 1;
	state[getIndex_above(23, 44, 1)] = 1;
	state[getIndex_above(24, 25, 1)] = 1;
	state[getIndex_above(24, 26, 1)] = 1;
	state[getIndex_above(24, 27, 1)] = 1;
	state[getIndex_above(24, 28, 1)] = 1;
	state[getIndex_above(24, 29, 1)] = 1;
	state[getIndex_above(24, 30, 1)] = 1;
	state[getIndex_above(24, 31, 1)] = 1;
	state[getIndex_above(24, 32, 1)] = 1;
	state[getIndex_above(24, 33, 1)] = 1;
	state[getIndex_above(24, 34, 1)] = 1;
	state[getIndex_above(24, 35, 1)] = 1;
	state[getIndex_above(24, 36, 1)] = 1;
	state[getIndex_above(24, 37, 1)] = 1;
	state[getIndex_above(24, 38, 1)] = 1;
	state[getIndex_above(24, 39, 1)] = 1;
	state[getIndex_above(24, 40, 1)] = 1;
	state[getIndex_above(24, 41, 1)] = 1;
	state[getIndex_above(24, 42, 1)] = 1;
	state[getIndex_above(24, 43, 1)] = 1;
	state[getIndex_above(24, 44, 1)] = 1;
	state[getIndex_above(25, 26, 1)] = 1;
	state[getIndex_above(25, 27, 1)] = 1;
	state[getIndex_above(25, 28, 1)] = 1;
	state[getIndex_above(25, 29, 1)] = 1;
	state[getIndex_above(25, 30, 1)] = 1;
	state[getIndex_above(25, 31, 1)] = 1;
	state[getIndex_above(25, 32, 1)] = 1;
	state[getIndex_above(25, 33, 1)] = 1;
	state[getIndex_above(25, 34, 1)] = 1;
	state[getIndex_above(25, 35, 1)] = 1;
	state[getIndex_above(25, 36, 1)] = 1;
	state[getIndex_above(25, 37, 1)] = 1;
	state[getIndex_above(25, 38, 1)] = 1;
	state[getIndex_above(25, 39, 1)] = 1;
	state[getIndex_above(25, 40, 1)] = 1;
	state[getIndex_above(25, 41, 1)] = 1;
	state[getIndex_above(25, 42, 1)] = 1;
	state[getIndex_above(25, 43, 1)] = 1;
	state[getIndex_above(25, 44, 1)] = 1;
	state[getIndex_above(26, 27, 1)] = 1;
	state[getIndex_above(26, 28, 1)] = 1;
	state[getIndex_above(26, 29, 1)] = 1;
	state[getIndex_above(26, 30, 1)] = 1;
	state[getIndex_above(26, 31, 1)] = 1;
	state[getIndex_above(26, 32, 1)] = 1;
	state[getIndex_above(26, 33, 1)] = 1;
	state[getIndex_above(26, 34, 1)] = 1;
	state[getIndex_above(26, 35, 1)] = 1;
	state[getIndex_above(26, 36, 1)] = 1;
	state[getIndex_above(26, 37, 1)] = 1;
	state[getIndex_above(26, 38, 1)] = 1;
	state[getIndex_above(26, 39, 1)] = 1;
	state[getIndex_above(26, 40, 1)] = 1;
	state[getIndex_above(26, 41, 1)] = 1;
	state[getIndex_above(26, 42, 1)] = 1;
	state[getIndex_above(26, 43, 1)] = 1;
	state[getIndex_above(26, 44, 1)] = 1;
	state[getIndex_above(27, 28, 1)] = 1;
	state[getIndex_above(27, 29, 1)] = 1;
	state[getIndex_above(27, 30, 1)] = 1;
	state[getIndex_above(27, 31, 1)] = 1;
	state[getIndex_above(27, 32, 1)] = 1;
	state[getIndex_above(27, 33, 1)] = 1;
	state[getIndex_above(27, 34, 1)] = 1;
	state[getIndex_above(27, 35, 1)] = 1;
	state[getIndex_above(27, 36, 1)] = 1;
	state[getIndex_above(27, 37, 1)] = 1;
	state[getIndex_above(27, 38, 1)] = 1;
	state[getIndex_above(27, 39, 1)] = 1;
	state[getIndex_above(27, 40, 1)] = 1;
	state[getIndex_above(27, 41, 1)] = 1;
	state[getIndex_above(27, 42, 1)] = 1;
	state[getIndex_above(27, 43, 1)] = 1;
	state[getIndex_above(27, 44, 1)] = 1;
	state[getIndex_above(28, 29, 1)] = 1;
	state[getIndex_above(28, 30, 1)] = 1;
	state[getIndex_above(28, 31, 1)] = 1;
	state[getIndex_above(28, 32, 1)] = 1;
	state[getIndex_above(28, 33, 1)] = 1;
	state[getIndex_above(28, 34, 1)] = 1;
	state[getIndex_above(28, 35, 1)] = 1;
	state[getIndex_above(28, 36, 1)] = 1;
	state[getIndex_above(28, 37, 1)] = 1;
	state[getIndex_above(28, 38, 1)] = 1;
	state[getIndex_above(28, 39, 1)] = 1;
	state[getIndex_above(28, 40, 1)] = 1;
	state[getIndex_above(28, 41, 1)] = 1;
	state[getIndex_above(28, 42, 1)] = 1;
	state[getIndex_above(28, 43, 1)] = 1;
	state[getIndex_above(28, 44, 1)] = 1;
	state[getIndex_above(29, 30, 1)] = 1;
	state[getIndex_above(29, 31, 1)] = 1;
	state[getIndex_above(29, 32, 1)] = 1;
	state[getIndex_above(29, 33, 1)] = 1;
	state[getIndex_above(29, 34, 1)] = 1;
	state[getIndex_above(29, 35, 1)] = 1;
	state[getIndex_above(29, 36, 1)] = 1;
	state[getIndex_above(29, 37, 1)] = 1;
	state[getIndex_above(29, 38, 1)] = 1;
	state[getIndex_above(29, 39, 1)] = 1;
	state[getIndex_above(29, 40, 1)] = 1;
	state[getIndex_above(29, 41, 1)] = 1;
	state[getIndex_above(29, 42, 1)] = 1;
	state[getIndex_above(29, 43, 1)] = 1;
	state[getIndex_above(29, 44, 1)] = 1;
	state[getIndex_above(30, 31, 1)] = 1;
	state[getIndex_above(30, 32, 1)] = 1;
	state[getIndex_above(30, 33, 1)] = 1;
	state[getIndex_above(30, 34, 1)] = 1;
	state[getIndex_above(30, 35, 1)] = 1;
	state[getIndex_above(30, 36, 1)] = 1;
	state[getIndex_above(30, 37, 1)] = 1;
	state[getIndex_above(30, 38, 1)] = 1;
	state[getIndex_above(30, 39, 1)] = 1;
	state[getIndex_above(30, 40, 1)] = 1;
	state[getIndex_above(30, 41, 1)] = 1;
	state[getIndex_above(30, 42, 1)] = 1;
	state[getIndex_above(30, 43, 1)] = 1;
	state[getIndex_above(30, 44, 1)] = 1;
	state[getIndex_above(31, 32, 1)] = 1;
	state[getIndex_above(31, 33, 1)] = 1;
	state[getIndex_above(31, 34, 1)] = 1;
	state[getIndex_above(31, 35, 1)] = 1;
	state[getIndex_above(31, 36, 1)] = 1;
	state[getIndex_above(31, 37, 1)] = 1;
	state[getIndex_above(31, 38, 1)] = 1;
	state[getIndex_above(31, 39, 1)] = 1;
	state[getIndex_above(31, 40, 1)] = 1;
	state[getIndex_above(31, 41, 1)] = 1;
	state[getIndex_above(31, 42, 1)] = 1;
	state[getIndex_above(31, 43, 1)] = 1;
	state[getIndex_above(31, 44, 1)] = 1;
	state[getIndex_above(32, 33, 1)] = 1;
	state[getIndex_above(32, 34, 1)] = 1;
	state[getIndex_above(32, 35, 1)] = 1;
	state[getIndex_above(32, 36, 1)] = 1;
	state[getIndex_above(32, 37, 1)] = 1;
	state[getIndex_above(32, 38, 1)] = 1;
	state[getIndex_above(32, 39, 1)] = 1;
	state[getIndex_above(32, 40, 1)] = 1;
	state[getIndex_above(32, 41, 1)] = 1;
	state[getIndex_above(32, 42, 1)] = 1;
	state[getIndex_above(32, 43, 1)] = 1;
	state[getIndex_above(32, 44, 1)] = 1;
	state[getIndex_above(33, 34, 1)] = 1;
	state[getIndex_above(33, 35, 1)] = 1;
	state[getIndex_above(33, 36, 1)] = 1;
	state[getIndex_above(33, 37, 1)] = 1;
	state[getIndex_above(33, 38, 1)] = 1;
	state[getIndex_above(33, 39, 1)] = 1;
	state[getIndex_above(33, 40, 1)] = 1;
	state[getIndex_above(33, 41, 1)] = 1;
	state[getIndex_above(33, 42, 1)] = 1;
	state[getIndex_above(33, 43, 1)] = 1;
	state[getIndex_above(33, 44, 1)] = 1;
	state[getIndex_above(34, 35, 1)] = 1;
	state[getIndex_above(34, 36, 1)] = 1;
	state[getIndex_above(34, 37, 1)] = 1;
	state[getIndex_above(34, 38, 1)] = 1;
	state[getIndex_above(34, 39, 1)] = 1;
	state[getIndex_above(34, 40, 1)] = 1;
	state[getIndex_above(34, 41, 1)] = 1;
	state[getIndex_above(34, 42, 1)] = 1;
	state[getIndex_above(34, 43, 1)] = 1;
	state[getIndex_above(34, 44, 1)] = 1;
	state[getIndex_above(35, 36, 1)] = 1;
	state[getIndex_above(35, 37, 1)] = 1;
	state[getIndex_above(35, 38, 1)] = 1;
	state[getIndex_above(35, 39, 1)] = 1;
	state[getIndex_above(35, 40, 1)] = 1;
	state[getIndex_above(35, 41, 1)] = 1;
	state[getIndex_above(35, 42, 1)] = 1;
	state[getIndex_above(35, 43, 1)] = 1;
	state[getIndex_above(35, 44, 1)] = 1;
	state[getIndex_above(36, 37, 1)] = 1;
	state[getIndex_above(36, 38, 1)] = 1;
	state[getIndex_above(36, 39, 1)] = 1;
	state[getIndex_above(36, 40, 1)] = 1;
	state[getIndex_above(36, 41, 1)] = 1;
	state[getIndex_above(36, 42, 1)] = 1;
	state[getIndex_above(36, 43, 1)] = 1;
	state[getIndex_above(36, 44, 1)] = 1;
	state[getIndex_above(37, 38, 1)] = 1;
	state[getIndex_above(37, 39, 1)] = 1;
	state[getIndex_above(37, 40, 1)] = 1;
	state[getIndex_above(37, 41, 1)] = 1;
	state[getIndex_above(37, 42, 1)] = 1;
	state[getIndex_above(37, 43, 1)] = 1;
	state[getIndex_above(37, 44, 1)] = 1;
	state[getIndex_above(38, 39, 1)] = 1;
	state[getIndex_above(38, 40, 1)] = 1;
	state[getIndex_above(38, 41, 1)] = 1;
	state[getIndex_above(38, 42, 1)] = 1;
	state[getIndex_above(38, 43, 1)] = 1;
	state[getIndex_above(38, 44, 1)] = 1;
	state[getIndex_above(39, 40, 1)] = 1;
	state[getIndex_above(39, 41, 1)] = 1;
	state[getIndex_above(39, 42, 1)] = 1;
	state[getIndex_above(39, 43, 1)] = 1;
	state[getIndex_above(39, 44, 1)] = 1;
	state[getIndex_above(40, 41, 1)] = 1;
	state[getIndex_above(40, 42, 1)] = 1;
	state[getIndex_above(40, 43, 1)] = 1;
	state[getIndex_above(40, 44, 1)] = 1;
	state[getIndex_above(41, 42, 1)] = 1;
	state[getIndex_above(41, 43, 1)] = 1;
	state[getIndex_above(41, 44, 1)] = 1;
	state[getIndex_above(42, 43, 1)] = 1;
	state[getIndex_above(42, 44, 1)] = 1;
	state[getIndex_above(43, 44, 1)] = 1;
	state[getIndex_origin(0, 30, 1)] = 1;
	state[getIndex_destin(0, 36, 1)] = 1;
	state[getIndex_origin(1, 27, 1)] = 1;
	state[getIndex_destin(1, 17, 1)] = 1;
	state[getIndex_origin(2, 15, 1)] = 1;
	state[getIndex_destin(2, 27, 1)] = 1;
	state[getIndex_origin(3, 43, 1)] = 1;
	state[getIndex_destin(3, 32, 1)] = 1;
	state[getIndex_origin(4, 30, 1)] = 1;
	state[getIndex_destin(4, 24, 1)] = 1;
	state[getIndex_origin(5, 29, 1)] = 1;
	state[getIndex_destin(5, 35, 1)] = 1;
	state[getIndex_origin(6, 34, 1)] = 1;
	state[getIndex_destin(6, 17, 1)] = 1;
	state[getIndex_origin(7, 24, 1)] = 1;
	state[getIndex_destin(7, 33, 1)] = 1;
	state[getIndex_origin(8, 18, 1)] = 1;
	state[getIndex_destin(8, 35, 1)] = 1;
	state[getIndex_origin(9, 28, 1)] = 1;
	state[getIndex_destin(9, 34, 1)] = 1;
	state[getIndex_origin(10, 33, 1)] = 1;
	state[getIndex_destin(10, 28, 1)] = 1;
	state[getIndex_origin(11, 43, 1)] = 1;
	state[getIndex_destin(11, 27, 1)] = 1;
	state[getIndex_origin(12, 42, 1)] = 1;
	state[getIndex_destin(12, 25, 1)] = 1;
	state[getIndex_origin(13, 42, 1)] = 1;
	state[getIndex_destin(13, 34, 1)] = 1;
	state[getIndex_origin(14, 23, 1)] = 1;
	state[getIndex_destin(14, 15, 1)] = 1;
	state[getIndex_lift_at(15, 1)] = 1;
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
			if(index0 >= 0 && index0 < 45){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 45){
					board(object[index0], object[index1]);
				}
			}
			break;
		case 2:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 45){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 45){
					depart(object[index0], object[index1]);
				}
			}
			break;
		case 3:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 45){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 45){
					up(object[index0], object[index1]);
				}
			}
			break;
		case 4:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 45){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 45){
					down(object[index0], object[index1]);
				}
			}
			break;
		}
		//check if goal state reached
		if((state[getIndex_served(0, 0)] && state[getIndex_served(1, 0)] && state[getIndex_served(2, 0)] && state[getIndex_served(3, 0)] && state[getIndex_served(4, 0)] && state[getIndex_served(5, 0)] && state[getIndex_served(6, 0)] && state[getIndex_served(7, 0)] && state[getIndex_served(8, 0)] && state[getIndex_served(9, 0)] && state[getIndex_served(10, 0)] && state[getIndex_served(11, 0)] && state[getIndex_served(12, 0)] && state[getIndex_served(13, 0)] && state[getIndex_served(14, 0)])){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}
