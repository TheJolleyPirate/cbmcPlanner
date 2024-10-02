//PREAMBLE
//action translation:
//push_start==push-start
//push_end==push-end
//pop_start==pop-start
//pop_end==pop-end
//push_unitarypipe==push-unitarypipe
//pop_unitarypipe==pop-unitarypipe
//END OF PREAMBLE
#include<stdio.h>
#include <stdlib.h>
int nondet_Int();
//problem definition
//state
int n = 5925;
char state[5925];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
//object translation:
//objectNames = {lco, gasoleo, rat-a, oca1, oc1b, b10, b21, b17, b14, b4, b6, b15, b19, b20, b13, b8, b2, b11, b5, b0, b1, b18, b7, b9, b12, b3, b16, a1, a2, a3, a4, a5, s12, s13, s34, s23, s15, ta1-1-lco, ta1-1-gasoleo, ta1-1-rat-a, ta1-1-oca1, ta1-1-oc1b, ta2-1-lco, ta2-1-gasoleo, ta2-1-rat-a, ta2-1-oca1, ta2-1-oc1b, ta3-1-lco, ta3-1-gasoleo, ta3-1-rat-a, ta3-3-oca1, ta3-2-oca1, ta3-1-oca1, ta3-1-oc1b, ta4-1-lco, ta4-1-gasoleo, ta4-1-rat-a, ta4-1-oca1, ta4-1-oc1b, ta5-1-lco, ta5-1-gasoleo, ta5-1-rat-a, ta5-1-oca1, ta5-1-oc1b};
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
int pipe[] = {32, 33, 34, 35, 36};
int area[] = {27, 28, 29, 30, 31};
int product[] = {0, 1, 2, 3, 4};
int batch_atom[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
int tank_slot[] = {37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
//predicates
int connect[64][64][64];
int unitary[64];
int not_unitary[64];
int last[64][64];
int first[64][64];
int follow[64][64];
int is_product[64][64];
int on[64][64];
int may_interface[64][64];
int normal[64];
int push_updating[64];
int pop_updating[64];
int tank_slot_product_location[64][64][64];
int occupied[64];
int not_occupied[64];
int equals[64][64];

//get index functions
int getIndex_connect(int x0, int x1, int x2, int set){
	int index;
	if(connect[x0][x1][x2] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			connect[x0][x1][x2] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = connect[x0][x1][x2];
	}
	return index;
}
int getIndex_unitary(int x0, int set){
	int index;
	if(unitary[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			unitary[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = unitary[x0];
	}
	return index;
}
int getIndex_not_unitary(int x0, int set){
	int index;
	if(not_unitary[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			not_unitary[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = not_unitary[x0];
	}
	return index;
}
int getIndex_last(int x0, int x1, int set){
	int index;
	if(last[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			last[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = last[x0][x1];
	}
	return index;
}
int getIndex_first(int x0, int x1, int set){
	int index;
	if(first[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			first[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = first[x0][x1];
	}
	return index;
}
int getIndex_follow(int x0, int x1, int set){
	int index;
	if(follow[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			follow[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = follow[x0][x1];
	}
	return index;
}
int getIndex_is_product(int x0, int x1, int set){
	int index;
	if(is_product[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			is_product[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = is_product[x0][x1];
	}
	return index;
}
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
int getIndex_may_interface(int x0, int x1, int set){
	int index;
	if(may_interface[x0][x1] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			may_interface[x0][x1] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = may_interface[x0][x1];
	}
	return index;
}
int getIndex_normal(int x0, int set){
	int index;
	if(normal[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			normal[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = normal[x0];
	}
	return index;
}
int getIndex_push_updating(int x0, int set){
	int index;
	if(push_updating[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			push_updating[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = push_updating[x0];
	}
	return index;
}
int getIndex_pop_updating(int x0, int set){
	int index;
	if(pop_updating[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			pop_updating[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = pop_updating[x0];
	}
	return index;
}
int getIndex_tank_slot_product_location(int x0, int x1, int x2, int set){
	int index;
	if(tank_slot_product_location[x0][x1][x2] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			tank_slot_product_location[x0][x1][x2] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = tank_slot_product_location[x0][x1][x2];
	}
	return index;
}
int getIndex_occupied(int x0, int set){
	int index;
	if(occupied[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			occupied[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = occupied[x0];
	}
	return index;
}
int getIndex_not_occupied(int x0, int set){
	int index;
	if(not_occupied[x0] < 0){
		if(set){
			if(nextIndex >= n) {
				exit(-1);
			}
			index = nextIndex;
			nextIndex += 1;
			not_occupied[x0] = index;
		}
		else{
			index = 0;
		}
	}
	else{
		index = not_occupied[x0];
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
void push_start(int pipe, int batch_atom_in, int from_area, int to_area, int first_batch_atom, int product_batch_atom_in, int product_first_batch, int tank_slot){
	if((state[getIndex_normal(pipe, 0)] && state[getIndex_not_unitary(pipe, 0)] && state[getIndex_connect(from_area, to_area, pipe, 0)] && state[getIndex_first(first_batch_atom, pipe, 0)] && state[getIndex_on(batch_atom_in, from_area, 0)] && state[getIndex_is_product(batch_atom_in, product_batch_atom_in, 0)] && state[getIndex_is_product(first_batch_atom, product_first_batch, 0)] && state[getIndex_may_interface(product_batch_atom_in, product_first_batch, 0)] && state[getIndex_tank_slot_product_location(tank_slot, product_batch_atom_in, from_area, 0)] && state[getIndex_occupied(tank_slot, 0)])){
		state[getIndex_normal(pipe, 1)] = 0;
		state[getIndex_first(first_batch_atom, pipe, 1)] = 0;
		state[getIndex_on(batch_atom_in, from_area, 1)] = 0;
		state[getIndex_occupied(tank_slot, 1)] = 0;
		state[getIndex_push_updating(pipe, 1)] = 1;
		state[getIndex_first(batch_atom_in, pipe, 1)] = 1;
		state[getIndex_follow(first_batch_atom, batch_atom_in, 1)] = 1;
		state[getIndex_not_occupied(tank_slot, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void push_end(int pipe, int from_area, int to_area, int last_batch_atom, int next_last_batch_atom, int product_last_batch, int tank_slot){
	if((state[getIndex_push_updating(pipe, 0)] && state[getIndex_not_unitary(pipe, 0)] && state[getIndex_connect(from_area, to_area, pipe, 0)] && state[getIndex_last(last_batch_atom, pipe, 0)] && state[getIndex_follow(last_batch_atom, next_last_batch_atom, 0)] && state[getIndex_is_product(last_batch_atom, product_last_batch, 0)] && state[getIndex_tank_slot_product_location(tank_slot, product_last_batch, to_area, 0)] && state[getIndex_not_occupied(tank_slot, 0)])){
		state[getIndex_push_updating(pipe, 1)] = 0;
		state[getIndex_follow(last_batch_atom, next_last_batch_atom, 1)] = 0;
		state[getIndex_last(last_batch_atom, pipe, 1)] = 0;
		state[getIndex_not_occupied(tank_slot, 1)] = 0;
		state[getIndex_normal(pipe, 1)] = 1;
		state[getIndex_last(next_last_batch_atom, pipe, 1)] = 1;
		state[getIndex_on(last_batch_atom, to_area, 1)] = 1;
		state[getIndex_occupied(tank_slot, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void pop_start(int pipe, int batch_atom_in, int from_area, int to_area, int last_batch_atom, int product_batch_atom_in, int product_last_batch, int tank_slot){
	if((state[getIndex_normal(pipe, 0)] && state[getIndex_not_unitary(pipe, 0)] && state[getIndex_connect(from_area, to_area, pipe, 0)] && state[getIndex_last(last_batch_atom, pipe, 0)] && state[getIndex_on(batch_atom_in, to_area, 0)] && state[getIndex_is_product(batch_atom_in, product_batch_atom_in, 0)] && state[getIndex_is_product(last_batch_atom, product_last_batch, 0)] && state[getIndex_may_interface(product_batch_atom_in, product_last_batch, 0)] && state[getIndex_tank_slot_product_location(tank_slot, product_batch_atom_in, to_area, 0)] && state[getIndex_occupied(tank_slot, 0)])){
		state[getIndex_normal(pipe, 1)] = 0;
		state[getIndex_last(last_batch_atom, pipe, 1)] = 0;
		state[getIndex_on(batch_atom_in, to_area, 1)] = 0;
		state[getIndex_occupied(tank_slot, 1)] = 0;
		state[getIndex_pop_updating(pipe, 1)] = 1;
		state[getIndex_last(batch_atom_in, pipe, 1)] = 1;
		state[getIndex_follow(batch_atom_in, last_batch_atom, 1)] = 1;
		state[getIndex_not_occupied(tank_slot, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void pop_end(int pipe, int from_area, int to_area, int first_batch_atom, int next_first_batch_atom, int product_first_batch, int tank_slot){
	if((state[getIndex_pop_updating(pipe, 0)] && state[getIndex_not_unitary(pipe, 0)] && state[getIndex_connect(from_area, to_area, pipe, 0)] && state[getIndex_first(first_batch_atom, pipe, 0)] && state[getIndex_follow(next_first_batch_atom, first_batch_atom, 0)] && state[getIndex_tank_slot_product_location(tank_slot, product_first_batch, from_area, 0)] && state[getIndex_not_occupied(tank_slot, 0)])){
		state[getIndex_pop_updating(pipe, 1)] = 0;
		state[getIndex_follow(next_first_batch_atom, first_batch_atom, 1)] = 0;
		state[getIndex_first(first_batch_atom, pipe, 1)] = 0;
		state[getIndex_not_occupied(tank_slot, 1)] = 0;
		state[getIndex_normal(pipe, 1)] = 1;
		state[getIndex_first(next_first_batch_atom, pipe, 1)] = 1;
		state[getIndex_on(first_batch_atom, from_area, 1)] = 1;
		state[getIndex_occupied(tank_slot, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void push_unitarypipe(int pipe, int batch_atom_in, int from_area, int to_area, int first_batch_atom, int product_batch_atom_in, int product_first_batch, int from_tank_slot, int to_tank_slot){
	if((state[getIndex_first(first_batch_atom, pipe, 0)] && state[getIndex_connect(from_area, to_area, pipe, 0)] && state[getIndex_on(batch_atom_in, from_area, 0)] && state[getIndex_unitary(pipe, 0)] && state[getIndex_is_product(batch_atom_in, product_batch_atom_in, 0)] && state[getIndex_is_product(first_batch_atom, product_first_batch, 0)] && state[getIndex_may_interface(product_batch_atom_in, product_first_batch, 0)] && state[getIndex_tank_slot_product_location(from_tank_slot, product_batch_atom_in, from_area, 0)] && state[getIndex_occupied(from_tank_slot, 0)] && state[getIndex_tank_slot_product_location(to_tank_slot, product_first_batch, to_area, 0)] && state[getIndex_not_occupied(to_tank_slot, 0)])){
		state[getIndex_first(first_batch_atom, pipe, 1)] = 0;
		state[getIndex_last(first_batch_atom, pipe, 1)] = 0;
		state[getIndex_on(batch_atom_in, from_area, 1)] = 0;
		state[getIndex_occupied(from_tank_slot, 1)] = 0;
		state[getIndex_not_occupied(to_tank_slot, 1)] = 0;
		state[getIndex_first(batch_atom_in, pipe, 1)] = 1;
		state[getIndex_last(batch_atom_in, pipe, 1)] = 1;
		state[getIndex_not_occupied(from_tank_slot, 1)] = 1;
		state[getIndex_on(first_batch_atom, to_area, 1)] = 1;
		state[getIndex_occupied(to_tank_slot, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
void pop_unitarypipe(int pipe, int batch_atom_in, int from_area, int to_area, int first_batch_atom, int product_batch_atom_in, int product_first_batch, int from_tank_slot, int to_tank_slot){
	if((state[getIndex_first(first_batch_atom, pipe, 0)] && state[getIndex_connect(from_area, to_area, pipe, 0)] && state[getIndex_on(batch_atom_in, to_area, 0)] && state[getIndex_unitary(pipe, 0)] && state[getIndex_is_product(batch_atom_in, product_batch_atom_in, 0)] && state[getIndex_is_product(first_batch_atom, product_first_batch, 0)] && state[getIndex_may_interface(product_batch_atom_in, product_first_batch, 0)] && state[getIndex_tank_slot_product_location(to_tank_slot, product_batch_atom_in, to_area, 0)] && state[getIndex_occupied(to_tank_slot, 0)] && state[getIndex_tank_slot_product_location(from_tank_slot, product_first_batch, from_area, 0)] && state[getIndex_not_occupied(from_tank_slot, 0)])){
		state[getIndex_last(first_batch_atom, pipe, 1)] = 0;
		state[getIndex_first(first_batch_atom, pipe, 1)] = 0;
		state[getIndex_on(batch_atom_in, to_area, 1)] = 0;
		state[getIndex_occupied(to_tank_slot, 1)] = 0;
		state[getIndex_not_occupied(from_tank_slot, 1)] = 0;
		state[getIndex_last(batch_atom_in, pipe, 1)] = 1;
		state[getIndex_first(batch_atom_in, pipe, 1)] = 1;
		state[getIndex_not_occupied(to_tank_slot, 1)] = 1;
		state[getIndex_on(first_batch_atom, from_area, 1)] = 1;
		state[getIndex_occupied(from_tank_slot, 1)] = 1;
	}
	else{
		exit(-1);
	}
	return;
}
//main loop
int main(){
	//setting connect to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			for(int i2 = 0; i2 < 64; i2++){
				connect[i0][i1][i2] = -1;
			}
		}
	}
	//setting unitary to -1
	for(int i0 = 0; i0 < 64; i0++){
		unitary[i0] = -1;
	}
	//setting not_unitary to -1
	for(int i0 = 0; i0 < 64; i0++){
		not_unitary[i0] = -1;
	}
	//setting last to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			last[i0][i1] = -1;
		}
	}
	//setting first to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			first[i0][i1] = -1;
		}
	}
	//setting follow to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			follow[i0][i1] = -1;
		}
	}
	//setting is_product to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			is_product[i0][i1] = -1;
		}
	}
	//setting on to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			on[i0][i1] = -1;
		}
	}
	//setting may_interface to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			may_interface[i0][i1] = -1;
		}
	}
	//setting normal to -1
	for(int i0 = 0; i0 < 64; i0++){
		normal[i0] = -1;
	}
	//setting push_updating to -1
	for(int i0 = 0; i0 < 64; i0++){
		push_updating[i0] = -1;
	}
	//setting pop_updating to -1
	for(int i0 = 0; i0 < 64; i0++){
		pop_updating[i0] = -1;
	}
	//setting tank_slot_product_location to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			for(int i2 = 0; i2 < 64; i2++){
				tank_slot_product_location[i0][i1][i2] = -1;
			}
		}
	}
	//setting occupied to -1
	for(int i0 = 0; i0 < 64; i0++){
		occupied[i0] = -1;
	}
	//setting not_occupied to -1
	for(int i0 = 0; i0 < 64; i0++){
		not_occupied[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 64; i0++){
		for(int i1 = 0; i1 < 64; i1++){
			equals[i0][i1] = -1;
		}
	}
	state[getIndex_normal(32, 1)] = 1;
	state[getIndex_normal(33, 1)] = 1;
	state[getIndex_normal(34, 1)] = 1;
	state[getIndex_normal(35, 1)] = 1;
	state[getIndex_normal(36, 1)] = 1;
	state[getIndex_may_interface(0, 0, 1)] = 1;
	state[getIndex_may_interface(1, 1, 1)] = 1;
	state[getIndex_may_interface(2, 2, 1)] = 1;
	state[getIndex_may_interface(3, 3, 1)] = 1;
	state[getIndex_may_interface(4, 4, 1)] = 1;
	state[getIndex_may_interface(0, 1, 1)] = 1;
	state[getIndex_may_interface(1, 0, 1)] = 1;
	state[getIndex_may_interface(0, 3, 1)] = 1;
	state[getIndex_may_interface(3, 0, 1)] = 1;
	state[getIndex_may_interface(0, 4, 1)] = 1;
	state[getIndex_may_interface(4, 0, 1)] = 1;
	state[getIndex_may_interface(0, 2, 1)] = 1;
	state[getIndex_may_interface(2, 0, 1)] = 1;
	state[getIndex_may_interface(1, 2, 1)] = 1;
	state[getIndex_may_interface(2, 1, 1)] = 1;
	state[getIndex_may_interface(1, 3, 1)] = 1;
	state[getIndex_may_interface(3, 1, 1)] = 1;
	state[getIndex_may_interface(1, 4, 1)] = 1;
	state[getIndex_may_interface(4, 1, 1)] = 1;
	state[getIndex_may_interface(3, 4, 1)] = 1;
	state[getIndex_may_interface(4, 3, 1)] = 1;
	state[getIndex_connect(27, 28, 32, 1)] = 1;
	state[getIndex_connect(27, 29, 33, 1)] = 1;
	state[getIndex_connect(29, 30, 34, 1)] = 1;
	state[getIndex_connect(28, 29, 35, 1)] = 1;
	state[getIndex_connect(27, 31, 36, 1)] = 1;
	state[getIndex_tank_slot_product_location(37, 0, 27, 1)] = 1;
	state[getIndex_tank_slot_product_location(38, 1, 27, 1)] = 1;
	state[getIndex_tank_slot_product_location(39, 2, 27, 1)] = 1;
	state[getIndex_tank_slot_product_location(40, 3, 27, 1)] = 1;
	state[getIndex_tank_slot_product_location(41, 4, 27, 1)] = 1;
	state[getIndex_tank_slot_product_location(42, 0, 28, 1)] = 1;
	state[getIndex_tank_slot_product_location(43, 1, 28, 1)] = 1;
	state[getIndex_tank_slot_product_location(44, 2, 28, 1)] = 1;
	state[getIndex_tank_slot_product_location(45, 3, 28, 1)] = 1;
	state[getIndex_tank_slot_product_location(46, 4, 28, 1)] = 1;
	state[getIndex_tank_slot_product_location(47, 0, 29, 1)] = 1;
	state[getIndex_tank_slot_product_location(48, 1, 29, 1)] = 1;
	state[getIndex_tank_slot_product_location(49, 2, 29, 1)] = 1;
	state[getIndex_tank_slot_product_location(50, 3, 29, 1)] = 1;
	state[getIndex_tank_slot_product_location(51, 3, 29, 1)] = 1;
	state[getIndex_tank_slot_product_location(52, 3, 29, 1)] = 1;
	state[getIndex_tank_slot_product_location(53, 4, 29, 1)] = 1;
	state[getIndex_tank_slot_product_location(54, 0, 30, 1)] = 1;
	state[getIndex_tank_slot_product_location(55, 1, 30, 1)] = 1;
	state[getIndex_tank_slot_product_location(56, 2, 30, 1)] = 1;
	state[getIndex_tank_slot_product_location(57, 3, 30, 1)] = 1;
	state[getIndex_tank_slot_product_location(58, 4, 30, 1)] = 1;
	state[getIndex_tank_slot_product_location(59, 0, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(60, 1, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(61, 2, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(62, 3, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(63, 4, 31, 1)] = 1;
	state[getIndex_is_product(5, 1, 1)] = 1;
	state[getIndex_is_product(6, 2, 1)] = 1;
	state[getIndex_is_product(7, 3, 1)] = 1;
	state[getIndex_is_product(8, 0, 1)] = 1;
	state[getIndex_is_product(9, 4, 1)] = 1;
	state[getIndex_is_product(10, 1, 1)] = 1;
	state[getIndex_is_product(11, 1, 1)] = 1;
	state[getIndex_is_product(12, 0, 1)] = 1;
	state[getIndex_is_product(13, 3, 1)] = 1;
	state[getIndex_is_product(14, 1, 1)] = 1;
	state[getIndex_is_product(15, 2, 1)] = 1;
	state[getIndex_is_product(16, 0, 1)] = 1;
	state[getIndex_is_product(17, 1, 1)] = 1;
	state[getIndex_is_product(18, 3, 1)] = 1;
	state[getIndex_is_product(19, 2, 1)] = 1;
	state[getIndex_is_product(20, 1, 1)] = 1;
	state[getIndex_is_product(21, 3, 1)] = 1;
	state[getIndex_is_product(22, 3, 1)] = 1;
	state[getIndex_is_product(23, 4, 1)] = 1;
	state[getIndex_is_product(24, 1, 1)] = 1;
	state[getIndex_is_product(25, 4, 1)] = 1;
	state[getIndex_is_product(26, 3, 1)] = 1;
	state[getIndex_on(5, 27, 1)] = 1;
	state[getIndex_occupied(38, 1)] = 1;
	state[getIndex_on(7, 30, 1)] = 1;
	state[getIndex_occupied(57, 1)] = 1;
	state[getIndex_on(9, 31, 1)] = 1;
	state[getIndex_occupied(63, 1)] = 1;
	state[getIndex_on(11, 30, 1)] = 1;
	state[getIndex_occupied(55, 1)] = 1;
	state[getIndex_on(12, 31, 1)] = 1;
	state[getIndex_occupied(59, 1)] = 1;
	state[getIndex_on(13, 29, 1)] = 1;
	state[getIndex_occupied(52, 1)] = 1;
	state[getIndex_on(16, 30, 1)] = 1;
	state[getIndex_occupied(54, 1)] = 1;
	state[getIndex_on(18, 29, 1)] = 1;
	state[getIndex_occupied(51, 1)] = 1;
	state[getIndex_on(19, 30, 1)] = 1;
	state[getIndex_occupied(56, 1)] = 1;
	state[getIndex_on(21, 29, 1)] = 1;
	state[getIndex_occupied(50, 1)] = 1;
	state[getIndex_not_occupied(37, 1)] = 1;
	state[getIndex_not_occupied(39, 1)] = 1;
	state[getIndex_not_occupied(40, 1)] = 1;
	state[getIndex_not_occupied(41, 1)] = 1;
	state[getIndex_not_occupied(42, 1)] = 1;
	state[getIndex_not_occupied(43, 1)] = 1;
	state[getIndex_not_occupied(44, 1)] = 1;
	state[getIndex_not_occupied(45, 1)] = 1;
	state[getIndex_not_occupied(46, 1)] = 1;
	state[getIndex_not_occupied(47, 1)] = 1;
	state[getIndex_not_occupied(48, 1)] = 1;
	state[getIndex_not_occupied(49, 1)] = 1;
	state[getIndex_not_occupied(53, 1)] = 1;
	state[getIndex_not_occupied(58, 1)] = 1;
	state[getIndex_not_occupied(60, 1)] = 1;
	state[getIndex_not_occupied(61, 1)] = 1;
	state[getIndex_not_occupied(62, 1)] = 1;
	state[getIndex_first(6, 32, 1)] = 1;
	state[getIndex_follow(17, 6, 1)] = 1;
	state[getIndex_last(17, 32, 1)] = 1;
	state[getIndex_first(14, 33, 1)] = 1;
	state[getIndex_follow(15, 14, 1)] = 1;
	state[getIndex_last(15, 33, 1)] = 1;
	state[getIndex_first(20, 34, 1)] = 1;
	state[getIndex_last(20, 34, 1)] = 1;
	state[getIndex_first(10, 35, 1)] = 1;
	state[getIndex_follow(23, 10, 1)] = 1;
	state[getIndex_follow(26, 23, 1)] = 1;
	state[getIndex_last(26, 35, 1)] = 1;
	state[getIndex_first(8, 36, 1)] = 1;
	state[getIndex_follow(24, 8, 1)] = 1;
	state[getIndex_follow(22, 24, 1)] = 1;
	state[getIndex_follow(25, 22, 1)] = 1;
	state[getIndex_last(25, 36, 1)] = 1;
	state[getIndex_not_unitary(32, 1)] = 1;
	state[getIndex_not_unitary(33, 1)] = 1;
	state[getIndex_unitary(34, 1)] = 1;
	state[getIndex_not_unitary(35, 1)] = 1;
	state[getIndex_not_unitary(36, 1)] = 1;
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
	state[getIndex_equals(57, 57, 1)] = 1;
	state[getIndex_equals(58, 58, 1)] = 1;
	state[getIndex_equals(59, 59, 1)] = 1;
	state[getIndex_equals(60, 60, 1)] = 1;
	state[getIndex_equals(61, 61, 1)] = 1;
	state[getIndex_equals(62, 62, 1)] = 1;
	state[getIndex_equals(63, 63, 1)] = 1;
	//decision variables
	int actionDecision;
	int index0;
	int index1;
	int index2;
	int index3;
	int index4;
	int index5;
	int index6;
	int index7;
	int index8;
	//main loop
	while(1 == 1){
		//choose action
		actionDecision = nondet_Int();
		switch(actionDecision){
		case 1:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 5){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 22){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 22){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 27){
											push_start(pipe[index0], batch_atom[index1], area[index2], area[index3], batch_atom[index4], product[index5], product[index6], tank_slot[index7]);
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		case 2:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 5){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 5){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 22){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 22){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 27){
										push_end(pipe[index0], area[index1], area[index2], batch_atom[index3], batch_atom[index4], product[index5], tank_slot[index6]);
									}
								}
							}
						}
					}
				}
			}
			break;
		case 3:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 5){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 22){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 22){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 27){
											pop_start(pipe[index0], batch_atom[index1], area[index2], area[index3], batch_atom[index4], product[index5], product[index6], tank_slot[index7]);
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		case 4:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 5){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 5){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 22){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 22){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 27){
										pop_end(pipe[index0], area[index1], area[index2], batch_atom[index3], batch_atom[index4], product[index5], tank_slot[index6]);
									}
								}
							}
						}
					}
				}
			}
			break;
		case 5:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 5){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 22){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 22){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 27){
											index8 = nondet_Int();
											if(index8 >= 0 && index8 < 27){
												push_unitarypipe(pipe[index0], batch_atom[index1], area[index2], area[index3], batch_atom[index4], product[index5], product[index6], tank_slot[index7], tank_slot[index8]);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		case 6:
 			index0 = nondet_Int();
			if(index0 >= 0 && index0 < 5){
				index1 = nondet_Int();
				if(index1 >= 0 && index1 < 22){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 22){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 27){
											index8 = nondet_Int();
											if(index8 >= 0 && index8 < 27){
												pop_unitarypipe(pipe[index0], batch_atom[index1], area[index2], area[index3], batch_atom[index4], product[index5], product[index6], tank_slot[index7], tank_slot[index8]);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		}
		//check if goal state reached
		if((state[getIndex_on(5, 29, 0)] && state[getIndex_on(24, 27, 0)] && state[getIndex_normal(32, 0)] && state[getIndex_normal(33, 0)] && state[getIndex_normal(34, 0)] && state[getIndex_normal(35, 0)] && state[getIndex_normal(36, 0)])){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}
