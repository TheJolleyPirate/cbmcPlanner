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
int n = 13282;
char state[13282];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
//object translation:
//objectNames = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31, f32, f33, f34, f35, f36, f37};
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56};
//predicates
int origin[57][57];
int floor[57];
int passenger[57];
int destin[57][57];
int above[57][57];
int boarded[57];
int served[57];
int lift_at[57];
int equals[57][57];

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
	for(int i0 = 0; i0 < 57; i0++){
		for(int i1 = 0; i1 < 57; i1++){
			origin[i0][i1] = -1;
		}
	}
	//setting floor to -1
	for(int i0 = 0; i0 < 57; i0++){
		floor[i0] = -1;
	}
	//setting passenger to -1
	for(int i0 = 0; i0 < 57; i0++){
		passenger[i0] = -1;
	}
	//setting destin to -1
	for(int i0 = 0; i0 < 57; i0++){
		for(int i1 = 0; i1 < 57; i1++){
			destin[i0][i1] = -1;
		}
	}
	//setting above to -1
	for(int i0 = 0; i0 < 57; i0++){
		for(int i1 = 0; i1 < 57; i1++){
			above[i0][i1] = -1;
		}
	}
	//setting boarded to -1
	for(int i0 = 0; i0 < 57; i0++){
		boarded[i0] = -1;
	}
	//setting served to -1
	for(int i0 = 0; i0 < 57; i0++){
		served[i0] = -1;
	}
	//setting lift_at to -1
	for(int i0 = 0; i0 < 57; i0++){
		lift_at[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 57; i0++){
		for(int i1 = 0; i1 < 57; i1++){
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
	state[getIndex_passenger(15, 1)] = 1;
	state[getIndex_passenger(16, 1)] = 1;
	state[getIndex_passenger(17, 1)] = 1;
	state[getIndex_passenger(18, 1)] = 1;
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
	state[getIndex_floor(45, 1)] = 1;
	state[getIndex_floor(46, 1)] = 1;
	state[getIndex_floor(47, 1)] = 1;
	state[getIndex_floor(48, 1)] = 1;
	state[getIndex_floor(49, 1)] = 1;
	state[getIndex_floor(50, 1)] = 1;
	state[getIndex_floor(51, 1)] = 1;
	state[getIndex_floor(52, 1)] = 1;
	state[getIndex_floor(53, 1)] = 1;
	state[getIndex_floor(54, 1)] = 1;
	state[getIndex_floor(55, 1)] = 1;
	state[getIndex_floor(56, 1)] = 1;
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
	state[getIndex_above(19, 45, 1)] = 1;
	state[getIndex_above(19, 46, 1)] = 1;
	state[getIndex_above(19, 47, 1)] = 1;
	state[getIndex_above(19, 48, 1)] = 1;
	state[getIndex_above(19, 49, 1)] = 1;
	state[getIndex_above(19, 50, 1)] = 1;
	state[getIndex_above(19, 51, 1)] = 1;
	state[getIndex_above(19, 52, 1)] = 1;
	state[getIndex_above(19, 53, 1)] = 1;
	state[getIndex_above(19, 54, 1)] = 1;
	state[getIndex_above(19, 55, 1)] = 1;
	state[getIndex_above(19, 56, 1)] = 1;
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
	state[getIndex_above(20, 45, 1)] = 1;
	state[getIndex_above(20, 46, 1)] = 1;
	state[getIndex_above(20, 47, 1)] = 1;
	state[getIndex_above(20, 48, 1)] = 1;
	state[getIndex_above(20, 49, 1)] = 1;
	state[getIndex_above(20, 50, 1)] = 1;
	state[getIndex_above(20, 51, 1)] = 1;
	state[getIndex_above(20, 52, 1)] = 1;
	state[getIndex_above(20, 53, 1)] = 1;
	state[getIndex_above(20, 54, 1)] = 1;
	state[getIndex_above(20, 55, 1)] = 1;
	state[getIndex_above(20, 56, 1)] = 1;
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
	state[getIndex_above(21, 45, 1)] = 1;
	state[getIndex_above(21, 46, 1)] = 1;
	state[getIndex_above(21, 47, 1)] = 1;
	state[getIndex_above(21, 48, 1)] = 1;
	state[getIndex_above(21, 49, 1)] = 1;
	state[getIndex_above(21, 50, 1)] = 1;
	state[getIndex_above(21, 51, 1)] = 1;
	state[getIndex_above(21, 52, 1)] = 1;
	state[getIndex_above(21, 53, 1)] = 1;
	state[getIndex_above(21, 54, 1)] = 1;
	state[getIndex_above(21, 55, 1)] = 1;
	state[getIndex_above(21, 56, 1)] = 1;
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
	state[getIndex_above(22, 45, 1)] = 1;
	state[getIndex_above(22, 46, 1)] = 1;
	state[getIndex_above(22, 47, 1)] = 1;
	state[getIndex_above(22, 48, 1)] = 1;
	state[getIndex_above(22, 49, 1)] = 1;
	state[getIndex_above(22, 50, 1)] = 1;
	state[getIndex_above(22, 51, 1)] = 1;
	state[getIndex_above(22, 52, 1)] = 1;
	state[getIndex_above(22, 53, 1)] = 1;
	state[getIndex_above(22, 54, 1)] = 1;
	state[getIndex_above(22, 55, 1)] = 1;
	state[getIndex_above(22, 56, 1)] = 1;
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
	state[getIndex_above(23, 45, 1)] = 1;
	state[getIndex_above(23, 46, 1)] = 1;
	state[getIndex_above(23, 47, 1)] = 1;
	state[getIndex_above(23, 48, 1)] = 1;
	state[getIndex_above(23, 49, 1)] = 1;
	state[getIndex_above(23, 50, 1)] = 1;
	state[getIndex_above(23, 51, 1)] = 1;
	state[getIndex_above(23, 52, 1)] = 1;
	state[getIndex_above(23, 53, 1)] = 1;
	state[getIndex_above(23, 54, 1)] = 1;
	state[getIndex_above(23, 55, 1)] = 1;
	state[getIndex_above(23, 56, 1)] = 1;
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
	state[getIndex_above(24, 45, 1)] = 1;
	state[getIndex_above(24, 46, 1)] = 1;
	state[getIndex_above(24, 47, 1)] = 1;
	state[getIndex_above(24, 48, 1)] = 1;
	state[getIndex_above(24, 49, 1)] = 1;
	state[getIndex_above(24, 50, 1)] = 1;
	state[getIndex_above(24, 51, 1)] = 1;
	state[getIndex_above(24, 52, 1)] = 1;
	state[getIndex_above(24, 53, 1)] = 1;
	state[getIndex_above(24, 54, 1)] = 1;
	state[getIndex_above(24, 55, 1)] = 1;
	state[getIndex_above(24, 56, 1)] = 1;
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
	state[getIndex_above(25, 45, 1)] = 1;
	state[getIndex_above(25, 46, 1)] = 1;
	state[getIndex_above(25, 47, 1)] = 1;
	state[getIndex_above(25, 48, 1)] = 1;
	state[getIndex_above(25, 49, 1)] = 1;
	state[getIndex_above(25, 50, 1)] = 1;
	state[getIndex_above(25, 51, 1)] = 1;
	state[getIndex_above(25, 52, 1)] = 1;
	state[getIndex_above(25, 53, 1)] = 1;
	state[getIndex_above(25, 54, 1)] = 1;
	state[getIndex_above(25, 55, 1)] = 1;
	state[getIndex_above(25, 56, 1)] = 1;
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
	state[getIndex_above(26, 45, 1)] = 1;
	state[getIndex_above(26, 46, 1)] = 1;
	state[getIndex_above(26, 47, 1)] = 1;
	state[getIndex_above(26, 48, 1)] = 1;
	state[getIndex_above(26, 49, 1)] = 1;
	state[getIndex_above(26, 50, 1)] = 1;
	state[getIndex_above(26, 51, 1)] = 1;
	state[getIndex_above(26, 52, 1)] = 1;
	state[getIndex_above(26, 53, 1)] = 1;
	state[getIndex_above(26, 54, 1)] = 1;
	state[getIndex_above(26, 55, 1)] = 1;
	state[getIndex_above(26, 56, 1)] = 1;
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
	state[getIndex_above(27, 45, 1)] = 1;
	state[getIndex_above(27, 46, 1)] = 1;
	state[getIndex_above(27, 47, 1)] = 1;
	state[getIndex_above(27, 48, 1)] = 1;
	state[getIndex_above(27, 49, 1)] = 1;
	state[getIndex_above(27, 50, 1)] = 1;
	state[getIndex_above(27, 51, 1)] = 1;
	state[getIndex_above(27, 52, 1)] = 1;
	state[getIndex_above(27, 53, 1)] = 1;
	state[getIndex_above(27, 54, 1)] = 1;
	state[getIndex_above(27, 55, 1)] = 1;
	state[getIndex_above(27, 56, 1)] = 1;
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
	state[getIndex_above(28, 45, 1)] = 1;
	state[getIndex_above(28, 46, 1)] = 1;
	state[getIndex_above(28, 47, 1)] = 1;
	state[getIndex_above(28, 48, 1)] = 1;
	state[getIndex_above(28, 49, 1)] = 1;
	state[getIndex_above(28, 50, 1)] = 1;
	state[getIndex_above(28, 51, 1)] = 1;
	state[getIndex_above(28, 52, 1)] = 1;
	state[getIndex_above(28, 53, 1)] = 1;
	state[getIndex_above(28, 54, 1)] = 1;
	state[getIndex_above(28, 55, 1)] = 1;
	state[getIndex_above(28, 56, 1)] = 1;
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
	state[getIndex_above(29, 45, 1)] = 1;
	state[getIndex_above(29, 46, 1)] = 1;
	state[getIndex_above(29, 47, 1)] = 1;
	state[getIndex_above(29, 48, 1)] = 1;
	state[getIndex_above(29, 49, 1)] = 1;
	state[getIndex_above(29, 50, 1)] = 1;
	state[getIndex_above(29, 51, 1)] = 1;
	state[getIndex_above(29, 52, 1)] = 1;
	state[getIndex_above(29, 53, 1)] = 1;
	state[getIndex_above(29, 54, 1)] = 1;
	state[getIndex_above(29, 55, 1)] = 1;
	state[getIndex_above(29, 56, 1)] = 1;
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
	state[getIndex_above(30, 45, 1)] = 1;
	state[getIndex_above(30, 46, 1)] = 1;
	state[getIndex_above(30, 47, 1)] = 1;
	state[getIndex_above(30, 48, 1)] = 1;
	state[getIndex_above(30, 49, 1)] = 1;
	state[getIndex_above(30, 50, 1)] = 1;
	state[getIndex_above(30, 51, 1)] = 1;
	state[getIndex_above(30, 52, 1)] = 1;
	state[getIndex_above(30, 53, 1)] = 1;
	state[getIndex_above(30, 54, 1)] = 1;
	state[getIndex_above(30, 55, 1)] = 1;
	state[getIndex_above(30, 56, 1)] = 1;
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
	state[getIndex_above(31, 45, 1)] = 1;
	state[getIndex_above(31, 46, 1)] = 1;
	state[getIndex_above(31, 47, 1)] = 1;
	state[getIndex_above(31, 48, 1)] = 1;
	state[getIndex_above(31, 49, 1)] = 1;
	state[getIndex_above(31, 50, 1)] = 1;
	state[getIndex_above(31, 51, 1)] = 1;
	state[getIndex_above(31, 52, 1)] = 1;
	state[getIndex_above(31, 53, 1)] = 1;
	state[getIndex_above(31, 54, 1)] = 1;
	state[getIndex_above(31, 55, 1)] = 1;
	state[getIndex_above(31, 56, 1)] = 1;
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
	state[getIndex_above(32, 45, 1)] = 1;
	state[getIndex_above(32, 46, 1)] = 1;
	state[getIndex_above(32, 47, 1)] = 1;
	state[getIndex_above(32, 48, 1)] = 1;
	state[getIndex_above(32, 49, 1)] = 1;
	state[getIndex_above(32, 50, 1)] = 1;
	state[getIndex_above(32, 51, 1)] = 1;
	state[getIndex_above(32, 52, 1)] = 1;
	state[getIndex_above(32, 53, 1)] = 1;
	state[getIndex_above(32, 54, 1)] = 1;
	state[getIndex_above(32, 55, 1)] = 1;
	state[getIndex_above(32, 56, 1)] = 1;
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
	state[getIndex_above(33, 45, 1)] = 1;
	state[getIndex_above(33, 46, 1)] = 1;
	state[getIndex_above(33, 47, 1)] = 1;
	state[getIndex_above(33, 48, 1)] = 1;
	state[getIndex_above(33, 49, 1)] = 1;
	state[getIndex_above(33, 50, 1)] = 1;
	state[getIndex_above(33, 51, 1)] = 1;
	state[getIndex_above(33, 52, 1)] = 1;
	state[getIndex_above(33, 53, 1)] = 1;
	state[getIndex_above(33, 54, 1)] = 1;
	state[getIndex_above(33, 55, 1)] = 1;
	state[getIndex_above(33, 56, 1)] = 1;
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
	state[getIndex_above(34, 45, 1)] = 1;
	state[getIndex_above(34, 46, 1)] = 1;
	state[getIndex_above(34, 47, 1)] = 1;
	state[getIndex_above(34, 48, 1)] = 1;
	state[getIndex_above(34, 49, 1)] = 1;
	state[getIndex_above(34, 50, 1)] = 1;
	state[getIndex_above(34, 51, 1)] = 1;
	state[getIndex_above(34, 52, 1)] = 1;
	state[getIndex_above(34, 53, 1)] = 1;
	state[getIndex_above(34, 54, 1)] = 1;
	state[getIndex_above(34, 55, 1)] = 1;
	state[getIndex_above(34, 56, 1)] = 1;
	state[getIndex_above(35, 36, 1)] = 1;
	state[getIndex_above(35, 37, 1)] = 1;
	state[getIndex_above(35, 38, 1)] = 1;
	state[getIndex_above(35, 39, 1)] = 1;
	state[getIndex_above(35, 40, 1)] = 1;
	state[getIndex_above(35, 41, 1)] = 1;
	state[getIndex_above(35, 42, 1)] = 1;
	state[getIndex_above(35, 43, 1)] = 1;
	state[getIndex_above(35, 44, 1)] = 1;
	state[getIndex_above(35, 45, 1)] = 1;
	state[getIndex_above(35, 46, 1)] = 1;
	state[getIndex_above(35, 47, 1)] = 1;
	state[getIndex_above(35, 48, 1)] = 1;
	state[getIndex_above(35, 49, 1)] = 1;
	state[getIndex_above(35, 50, 1)] = 1;
	state[getIndex_above(35, 51, 1)] = 1;
	state[getIndex_above(35, 52, 1)] = 1;
	state[getIndex_above(35, 53, 1)] = 1;
	state[getIndex_above(35, 54, 1)] = 1;
	state[getIndex_above(35, 55, 1)] = 1;
	state[getIndex_above(35, 56, 1)] = 1;
	state[getIndex_above(36, 37, 1)] = 1;
	state[getIndex_above(36, 38, 1)] = 1;
	state[getIndex_above(36, 39, 1)] = 1;
	state[getIndex_above(36, 40, 1)] = 1;
	state[getIndex_above(36, 41, 1)] = 1;
	state[getIndex_above(36, 42, 1)] = 1;
	state[getIndex_above(36, 43, 1)] = 1;
	state[getIndex_above(36, 44, 1)] = 1;
	state[getIndex_above(36, 45, 1)] = 1;
	state[getIndex_above(36, 46, 1)] = 1;
	state[getIndex_above(36, 47, 1)] = 1;
	state[getIndex_above(36, 48, 1)] = 1;
	state[getIndex_above(36, 49, 1)] = 1;
	state[getIndex_above(36, 50, 1)] = 1;
	state[getIndex_above(36, 51, 1)] = 1;
	state[getIndex_above(36, 52, 1)] = 1;
	state[getIndex_above(36, 53, 1)] = 1;
	state[getIndex_above(36, 54, 1)] = 1;
	state[getIndex_above(36, 55, 1)] = 1;
	state[getIndex_above(36, 56, 1)] = 1;
	state[getIndex_above(37, 38, 1)] = 1;
	state[getIndex_above(37, 39, 1)] = 1;
	state[getIndex_above(37, 40, 1)] = 1;
	state[getIndex_above(37, 41, 1)] = 1;
	state[getIndex_above(37, 42, 1)] = 1;
	state[getIndex_above(37, 43, 1)] = 1;
	state[getIndex_above(37, 44, 1)] = 1;
	state[getIndex_above(37, 45, 1)] = 1;
	state[getIndex_above(37, 46, 1)] = 1;
	state[getIndex_above(37, 47, 1)] = 1;
	state[getIndex_above(37, 48, 1)] = 1;
	state[getIndex_above(37, 49, 1)] = 1;
	state[getIndex_above(37, 50, 1)] = 1;
	state[getIndex_above(37, 51, 1)] = 1;
	state[getIndex_above(37, 52, 1)] = 1;
	state[getIndex_above(37, 53, 1)] = 1;
	state[getIndex_above(37, 54, 1)] = 1;
	state[getIndex_above(37, 55, 1)] = 1;
	state[getIndex_above(37, 56, 1)] = 1;
	state[getIndex_above(38, 39, 1)] = 1;
	state[getIndex_above(38, 40, 1)] = 1;
	state[getIndex_above(38, 41, 1)] = 1;
	state[getIndex_above(38, 42, 1)] = 1;
	state[getIndex_above(38, 43, 1)] = 1;
	state[getIndex_above(38, 44, 1)] = 1;
	state[getIndex_above(38, 45, 1)] = 1;
	state[getIndex_above(38, 46, 1)] = 1;
	state[getIndex_above(38, 47, 1)] = 1;
	state[getIndex_above(38, 48, 1)] = 1;
	state[getIndex_above(38, 49, 1)] = 1;
	state[getIndex_above(38, 50, 1)] = 1;
	state[getIndex_above(38, 51, 1)] = 1;
	state[getIndex_above(38, 52, 1)] = 1;
	state[getIndex_above(38, 53, 1)] = 1;
	state[getIndex_above(38, 54, 1)] = 1;
	state[getIndex_above(38, 55, 1)] = 1;
	state[getIndex_above(38, 56, 1)] = 1;
	state[getIndex_above(39, 40, 1)] = 1;
	state[getIndex_above(39, 41, 1)] = 1;
	state[getIndex_above(39, 42, 1)] = 1;
	state[getIndex_above(39, 43, 1)] = 1;
	state[getIndex_above(39, 44, 1)] = 1;
	state[getIndex_above(39, 45, 1)] = 1;
	state[getIndex_above(39, 46, 1)] = 1;
	state[getIndex_above(39, 47, 1)] = 1;
	state[getIndex_above(39, 48, 1)] = 1;
	state[getIndex_above(39, 49, 1)] = 1;
	state[getIndex_above(39, 50, 1)] = 1;
	state[getIndex_above(39, 51, 1)] = 1;
	state[getIndex_above(39, 52, 1)] = 1;
	state[getIndex_above(39, 53, 1)] = 1;
	state[getIndex_above(39, 54, 1)] = 1;
	state[getIndex_above(39, 55, 1)] = 1;
	state[getIndex_above(39, 56, 1)] = 1;
	state[getIndex_above(40, 41, 1)] = 1;
	state[getIndex_above(40, 42, 1)] = 1;
	state[getIndex_above(40, 43, 1)] = 1;
	state[getIndex_above(40, 44, 1)] = 1;
	state[getIndex_above(40, 45, 1)] = 1;
	state[getIndex_above(40, 46, 1)] = 1;
	state[getIndex_above(40, 47, 1)] = 1;
	state[getIndex_above(40, 48, 1)] = 1;
	state[getIndex_above(40, 49, 1)] = 1;
	state[getIndex_above(40, 50, 1)] = 1;
	state[getIndex_above(40, 51, 1)] = 1;
	state[getIndex_above(40, 52, 1)] = 1;
	state[getIndex_above(40, 53, 1)] = 1;
	state[getIndex_above(40, 54, 1)] = 1;
	state[getIndex_above(40, 55, 1)] = 1;
	state[getIndex_above(40, 56, 1)] = 1;
	state[getIndex_above(41, 42, 1)] = 1;
	state[getIndex_above(41, 43, 1)] = 1;
	state[getIndex_above(41, 44, 1)] = 1;
	state[getIndex_above(41, 45, 1)] = 1;
	state[getIndex_above(41, 46, 1)] = 1;
	state[getIndex_above(41, 47, 1)] = 1;
	state[getIndex_above(41, 48, 1)] = 1;
	state[getIndex_above(41, 49, 1)] = 1;
	state[getIndex_above(41, 50, 1)] = 1;
	state[getIndex_above(41, 51, 1)] = 1;
	state[getIndex_above(41, 52, 1)] = 1;
	state[getIndex_above(41, 53, 1)] = 1;
	state[getIndex_above(41, 54, 1)] = 1;
	state[getIndex_above(41, 55, 1)] = 1;
	state[getIndex_above(41, 56, 1)] = 1;
	state[getIndex_above(42, 43, 1)] = 1;
	state[getIndex_above(42, 44, 1)] = 1;
	state[getIndex_above(42, 45, 1)] = 1;
	state[getIndex_above(42, 46, 1)] = 1;
	state[getIndex_above(42, 47, 1)] = 1;
	state[getIndex_above(42, 48, 1)] = 1;
	state[getIndex_above(42, 49, 1)] = 1;
	state[getIndex_above(42, 50, 1)] = 1;
	state[getIndex_above(42, 51, 1)] = 1;
	state[getIndex_above(42, 52, 1)] = 1;
	state[getIndex_above(42, 53, 1)] = 1;
	state[getIndex_above(42, 54, 1)] = 1;
	state[getIndex_above(42, 55, 1)] = 1;
	state[getIndex_above(42, 56, 1)] = 1;
	state[getIndex_above(43, 44, 1)] = 1;
	state[getIndex_above(43, 45, 1)] = 1;
	state[getIndex_above(43, 46, 1)] = 1;
	state[getIndex_above(43, 47, 1)] = 1;
	state[getIndex_above(43, 48, 1)] = 1;
	state[getIndex_above(43, 49, 1)] = 1;
	state[getIndex_above(43, 50, 1)] = 1;
	state[getIndex_above(43, 51, 1)] = 1;
	state[getIndex_above(43, 52, 1)] = 1;
	state[getIndex_above(43, 53, 1)] = 1;
	state[getIndex_above(43, 54, 1)] = 1;
	state[getIndex_above(43, 55, 1)] = 1;
	state[getIndex_above(43, 56, 1)] = 1;
	state[getIndex_above(44, 45, 1)] = 1;
	state[getIndex_above(44, 46, 1)] = 1;
	state[getIndex_above(44, 47, 1)] = 1;
	state[getIndex_above(44, 48, 1)] = 1;
	state[getIndex_above(44, 49, 1)] = 1;
	state[getIndex_above(44, 50, 1)] = 1;
	state[getIndex_above(44, 51, 1)] = 1;
	state[getIndex_above(44, 52, 1)] = 1;
	state[getIndex_above(44, 53, 1)] = 1;
	state[getIndex_above(44, 54, 1)] = 1;
	state[getIndex_above(44, 55, 1)] = 1;
	state[getIndex_above(44, 56, 1)] = 1;
	state[getIndex_above(45, 46, 1)] = 1;
	state[getIndex_above(45, 47, 1)] = 1;
	state[getIndex_above(45, 48, 1)] = 1;
	state[getIndex_above(45, 49, 1)] = 1;
	state[getIndex_above(45, 50, 1)] = 1;
	state[getIndex_above(45, 51, 1)] = 1;
	state[getIndex_above(45, 52, 1)] = 1;
	state[getIndex_above(45, 53, 1)] = 1;
	state[getIndex_above(45, 54, 1)] = 1;
	state[getIndex_above(45, 55, 1)] = 1;
	state[getIndex_above(45, 56, 1)] = 1;
	state[getIndex_above(46, 47, 1)] = 1;
	state[getIndex_above(46, 48, 1)] = 1;
	state[getIndex_above(46, 49, 1)] = 1;
	state[getIndex_above(46, 50, 1)] = 1;
	state[getIndex_above(46, 51, 1)] = 1;
	state[getIndex_above(46, 52, 1)] = 1;
	state[getIndex_above(46, 53, 1)] = 1;
	state[getIndex_above(46, 54, 1)] = 1;
	state[getIndex_above(46, 55, 1)] = 1;
	state[getIndex_above(46, 56, 1)] = 1;
	state[getIndex_above(47, 48, 1)] = 1;
	state[getIndex_above(47, 49, 1)] = 1;
	state[getIndex_above(47, 50, 1)] = 1;
	state[getIndex_above(47, 51, 1)] = 1;
	state[getIndex_above(47, 52, 1)] = 1;
	state[getIndex_above(47, 53, 1)] = 1;
	state[getIndex_above(47, 54, 1)] = 1;
	state[getIndex_above(47, 55, 1)] = 1;
	state[getIndex_above(47, 56, 1)] = 1;
	state[getIndex_above(48, 49, 1)] = 1;
	state[getIndex_above(48, 50, 1)] = 1;
	state[getIndex_above(48, 51, 1)] = 1;
	state[getIndex_above(48, 52, 1)] = 1;
	state[getIndex_above(48, 53, 1)] = 1;
	state[getIndex_above(48, 54, 1)] = 1;
	state[getIndex_above(48, 55, 1)] = 1;
	state[getIndex_above(48, 56, 1)] = 1;
	state[getIndex_above(49, 50, 1)] = 1;
	state[getIndex_above(49, 51, 1)] = 1;
	state[getIndex_above(49, 52, 1)] = 1;
	state[getIndex_above(49, 53, 1)] = 1;
	state[getIndex_above(49, 54, 1)] = 1;
	state[getIndex_above(49, 55, 1)] = 1;
	state[getIndex_above(49, 56, 1)] = 1;
	state[getIndex_above(50, 51, 1)] = 1;
	state[getIndex_above(50, 52, 1)] = 1;
	state[getIndex_above(50, 53, 1)] = 1;
	state[getIndex_above(50, 54, 1)] = 1;
	state[getIndex_above(50, 55, 1)] = 1;
	state[getIndex_above(50, 56, 1)] = 1;
	state[getIndex_above(51, 52, 1)] = 1;
	state[getIndex_above(51, 53, 1)] = 1;
	state[getIndex_above(51, 54, 1)] = 1;
	state[getIndex_above(51, 55, 1)] = 1;
	state[getIndex_above(51, 56, 1)] = 1;
	state[getIndex_above(52, 53, 1)] = 1;
	state[getIndex_above(52, 54, 1)] = 1;
	state[getIndex_above(52, 55, 1)] = 1;
	state[getIndex_above(52, 56, 1)] = 1;
	state[getIndex_above(53, 54, 1)] = 1;
	state[getIndex_above(53, 55, 1)] = 1;
	state[getIndex_above(53, 56, 1)] = 1;
	state[getIndex_above(54, 55, 1)] = 1;
	state[getIndex_above(54, 56, 1)] = 1;
	state[getIndex_above(55, 56, 1)] = 1;
	state[getIndex_origin(0, 49, 1)] = 1;
	state[getIndex_destin(0, 56, 1)] = 1;
	state[getIndex_origin(1, 54, 1)] = 1;
	state[getIndex_destin(1, 47, 1)] = 1;
	state[getIndex_origin(2, 37, 1)] = 1;
	state[getIndex_destin(2, 50, 1)] = 1;
	state[getIndex_origin(3, 32, 1)] = 1;
	state[getIndex_destin(3, 33, 1)] = 1;
	state[getIndex_origin(4, 40, 1)] = 1;
	state[getIndex_destin(4, 52, 1)] = 1;
	state[getIndex_origin(5, 55, 1)] = 1;
	state[getIndex_destin(5, 49, 1)] = 1;
	state[getIndex_origin(6, 56, 1)] = 1;
	state[getIndex_destin(6, 34, 1)] = 1;
	state[getIndex_origin(7, 31, 1)] = 1;
	state[getIndex_destin(7, 44, 1)] = 1;
	state[getIndex_origin(8, 33, 1)] = 1;
	state[getIndex_destin(8, 27, 1)] = 1;
	state[getIndex_origin(9, 21, 1)] = 1;
	state[getIndex_destin(9, 48, 1)] = 1;
	state[getIndex_origin(10, 47, 1)] = 1;
	state[getIndex_destin(10, 28, 1)] = 1;
	state[getIndex_origin(11, 35, 1)] = 1;
	state[getIndex_destin(11, 24, 1)] = 1;
	state[getIndex_origin(12, 39, 1)] = 1;
	state[getIndex_destin(12, 48, 1)] = 1;
	state[getIndex_origin(13, 54, 1)] = 1;
	state[getIndex_destin(13, 32, 1)] = 1;
	state[getIndex_origin(14, 22, 1)] = 1;
	state[getIndex_destin(14, 51, 1)] = 1;
	state[getIndex_origin(15, 41, 1)] = 1;
	state[getIndex_destin(15, 53, 1)] = 1;
	state[getIndex_origin(16, 28, 1)] = 1;
	state[getIndex_destin(16, 38, 1)] = 1;
	state[getIndex_origin(17, 21, 1)] = 1;
	state[getIndex_destin(17, 46, 1)] = 1;
	state[getIndex_origin(18, 31, 1)] = 1;
	state[getIndex_destin(18, 51, 1)] = 1;
	state[getIndex_lift_at(19, 1)] = 1;
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
	state[getIndex_equals(50, 50, 1)] = 1;
	state[getIndex_equals(51, 51, 1)] = 1;
	state[getIndex_equals(52, 52, 1)] = 1;
	state[getIndex_equals(53, 53, 1)] = 1;
	state[getIndex_equals(54, 54, 1)] = 1;
	state[getIndex_equals(55, 55, 1)] = 1;
	state[getIndex_equals(56, 56, 1)] = 1;
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
			if(index0 >= 0 && index0 < 57){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 57){
					board(object[index0], object[index1]);
				}
			}
			break;
		case 2:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 57){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 57){
					depart(object[index0], object[index1]);
				}
			}
			break;
		case 3:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 57){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 57){
					up(object[index0], object[index1]);
				}
			}
			break;
		case 4:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 57){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 57){
					down(object[index0], object[index1]);
				}
			}
			break;
		}
		//check if goal state reached
		if((state[getIndex_served(0, 0)] && state[getIndex_served(1, 0)] && state[getIndex_served(2, 0)] && state[getIndex_served(3, 0)] && state[getIndex_served(4, 0)] && state[getIndex_served(5, 0)] && state[getIndex_served(6, 0)] && state[getIndex_served(7, 0)] && state[getIndex_served(8, 0)] && state[getIndex_served(9, 0)] && state[getIndex_served(10, 0)] && state[getIndex_served(11, 0)] && state[getIndex_served(12, 0)] && state[getIndex_served(13, 0)] && state[getIndex_served(14, 0)] && state[getIndex_served(15, 0)] && state[getIndex_served(16, 0)] && state[getIndex_served(17, 0)] && state[getIndex_served(18, 0)])){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}