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
int n = 15583;
char state[15583];
//reserve state[0] to always be false
int nextIndex = 1;
//objects
//object translation:
//objectNames = {lco, gasoleo, rat-a, oca1, oc1b, b10, b21, b17, b14, b22, b4, b6, b15, b19, b20, b13, b8, b2, b11, b24, b5, b0, b1, b25, b18, b7, b12, b9, b3, b23, b16, a1, a2, a3, a4, a5, s12, s13, s34, s23, s15, ta1-4-lco, ta1-3-lco, ta1-2-lco, ta1-1-lco, ta1-3-gasoleo, ta1-2-gasoleo, ta1-1-gasoleo, ta1-3-rat-a, ta1-2-rat-a, ta1-1-rat-a, ta1-2-oca1, ta1-1-oca1, ta1-2-oc1b, ta1-1-oc1b, ta2-4-lco, ta2-3-lco, ta2-2-lco, ta2-1-lco, ta2-3-gasoleo, ta2-2-gasoleo, ta2-1-gasoleo, ta2-3-rat-a, ta2-2-rat-a, ta2-1-rat-a, ta2-2-oca1, ta2-1-oca1, ta2-2-oc1b, ta2-1-oc1b, ta3-4-lco, ta3-3-lco, ta3-2-lco, ta3-1-lco, ta3-3-gasoleo, ta3-2-gasoleo, ta3-1-gasoleo, ta3-3-rat-a, ta3-2-rat-a, ta3-1-rat-a, ta3-2-oca1, ta3-1-oca1, ta3-2-oc1b, ta3-1-oc1b, ta4-4-lco, ta4-3-lco, ta4-2-lco, ta4-1-lco, ta4-3-gasoleo, ta4-2-gasoleo, ta4-1-gasoleo, ta4-3-rat-a, ta4-2-rat-a, ta4-1-rat-a, ta4-2-oca1, ta4-1-oca1, ta4-2-oc1b, ta4-1-oc1b, ta5-4-lco, ta5-3-lco, ta5-2-lco, ta5-1-lco, ta5-3-gasoleo, ta5-2-gasoleo, ta5-1-gasoleo, ta5-3-rat-a, ta5-2-rat-a, ta5-1-rat-a, ta5-2-oca1, ta5-1-oca1, ta5-2-oc1b, ta5-1-oc1b};
int object[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
int pipe[] = {36, 37, 38, 39, 40};
int area[] = {31, 32, 33, 34, 35};
int product[] = {0, 1, 2, 3, 4};
int batch_atom[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
int tank_slot[] = {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
//predicates
int connect[111][111][111];
int unitary[111];
int not_unitary[111];
int last[111][111];
int first[111][111];
int follow[111][111];
int is_product[111][111];
int on[111][111];
int may_interface[111][111];
int normal[111];
int push_updating[111];
int pop_updating[111];
int tank_slot_product_location[111][111][111];
int occupied[111];
int not_occupied[111];
int equals[111][111];

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
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			for(int i2 = 0; i2 < 111; i2++){
				connect[i0][i1][i2] = -1;
			}
		}
	}
	//setting unitary to -1
	for(int i0 = 0; i0 < 111; i0++){
		unitary[i0] = -1;
	}
	//setting not_unitary to -1
	for(int i0 = 0; i0 < 111; i0++){
		not_unitary[i0] = -1;
	}
	//setting last to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			last[i0][i1] = -1;
		}
	}
	//setting first to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			first[i0][i1] = -1;
		}
	}
	//setting follow to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			follow[i0][i1] = -1;
		}
	}
	//setting is_product to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			is_product[i0][i1] = -1;
		}
	}
	//setting on to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			on[i0][i1] = -1;
		}
	}
	//setting may_interface to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			may_interface[i0][i1] = -1;
		}
	}
	//setting normal to -1
	for(int i0 = 0; i0 < 111; i0++){
		normal[i0] = -1;
	}
	//setting push_updating to -1
	for(int i0 = 0; i0 < 111; i0++){
		push_updating[i0] = -1;
	}
	//setting pop_updating to -1
	for(int i0 = 0; i0 < 111; i0++){
		pop_updating[i0] = -1;
	}
	//setting tank_slot_product_location to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			for(int i2 = 0; i2 < 111; i2++){
				tank_slot_product_location[i0][i1][i2] = -1;
			}
		}
	}
	//setting occupied to -1
	for(int i0 = 0; i0 < 111; i0++){
		occupied[i0] = -1;
	}
	//setting not_occupied to -1
	for(int i0 = 0; i0 < 111; i0++){
		not_occupied[i0] = -1;
	}
	//setting equals to -1
	for(int i0 = 0; i0 < 111; i0++){
		for(int i1 = 0; i1 < 111; i1++){
			equals[i0][i1] = -1;
		}
	}
	state[getIndex_normal(36, 1)] = 1;
	state[getIndex_normal(37, 1)] = 1;
	state[getIndex_normal(38, 1)] = 1;
	state[getIndex_normal(39, 1)] = 1;
	state[getIndex_normal(40, 1)] = 1;
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
	state[getIndex_connect(31, 32, 36, 1)] = 1;
	state[getIndex_connect(31, 33, 37, 1)] = 1;
	state[getIndex_connect(33, 34, 38, 1)] = 1;
	state[getIndex_connect(32, 33, 39, 1)] = 1;
	state[getIndex_connect(31, 35, 40, 1)] = 1;
	state[getIndex_tank_slot_product_location(41, 0, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(42, 0, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(43, 0, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(44, 0, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(45, 1, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(46, 1, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(47, 1, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(48, 2, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(49, 2, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(50, 2, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(51, 3, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(52, 3, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(53, 4, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(54, 4, 31, 1)] = 1;
	state[getIndex_tank_slot_product_location(55, 0, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(56, 0, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(57, 0, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(58, 0, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(59, 1, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(60, 1, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(61, 1, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(62, 2, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(63, 2, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(64, 2, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(65, 3, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(66, 3, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(67, 4, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(68, 4, 32, 1)] = 1;
	state[getIndex_tank_slot_product_location(69, 0, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(70, 0, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(71, 0, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(72, 0, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(73, 1, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(74, 1, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(75, 1, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(76, 2, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(77, 2, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(78, 2, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(79, 3, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(80, 3, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(81, 4, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(82, 4, 33, 1)] = 1;
	state[getIndex_tank_slot_product_location(83, 0, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(84, 0, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(85, 0, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(86, 0, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(87, 1, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(88, 1, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(89, 1, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(90, 2, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(91, 2, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(92, 2, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(93, 3, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(94, 3, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(95, 4, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(96, 4, 34, 1)] = 1;
	state[getIndex_tank_slot_product_location(97, 0, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(98, 0, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(99, 0, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(100, 0, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(101, 1, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(102, 1, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(103, 1, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(104, 2, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(105, 2, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(106, 2, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(107, 3, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(108, 3, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(109, 4, 35, 1)] = 1;
	state[getIndex_tank_slot_product_location(110, 4, 35, 1)] = 1;
	state[getIndex_is_product(5, 2, 1)] = 1;
	state[getIndex_is_product(6, 2, 1)] = 1;
	state[getIndex_is_product(7, 1, 1)] = 1;
	state[getIndex_is_product(8, 3, 1)] = 1;
	state[getIndex_is_product(9, 4, 1)] = 1;
	state[getIndex_is_product(10, 0, 1)] = 1;
	state[getIndex_is_product(11, 1, 1)] = 1;
	state[getIndex_is_product(12, 2, 1)] = 1;
	state[getIndex_is_product(13, 1, 1)] = 1;
	state[getIndex_is_product(14, 0, 1)] = 1;
	state[getIndex_is_product(15, 1, 1)] = 1;
	state[getIndex_is_product(16, 0, 1)] = 1;
	state[getIndex_is_product(17, 1, 1)] = 1;
	state[getIndex_is_product(18, 2, 1)] = 1;
	state[getIndex_is_product(19, 3, 1)] = 1;
	state[getIndex_is_product(20, 2, 1)] = 1;
	state[getIndex_is_product(21, 0, 1)] = 1;
	state[getIndex_is_product(22, 0, 1)] = 1;
	state[getIndex_is_product(23, 0, 1)] = 1;
	state[getIndex_is_product(24, 3, 1)] = 1;
	state[getIndex_is_product(25, 2, 1)] = 1;
	state[getIndex_is_product(26, 0, 1)] = 1;
	state[getIndex_is_product(27, 0, 1)] = 1;
	state[getIndex_is_product(28, 3, 1)] = 1;
	state[getIndex_is_product(29, 4, 1)] = 1;
	state[getIndex_is_product(30, 4, 1)] = 1;
	state[getIndex_on(5, 33, 1)] = 1;
	state[getIndex_occupied(78, 1)] = 1;
	state[getIndex_on(6, 32, 1)] = 1;
	state[getIndex_occupied(64, 1)] = 1;
	state[getIndex_on(7, 35, 1)] = 1;
	state[getIndex_occupied(103, 1)] = 1;
	state[getIndex_on(10, 32, 1)] = 1;
	state[getIndex_occupied(58, 1)] = 1;
	state[getIndex_on(13, 34, 1)] = 1;
	state[getIndex_occupied(89, 1)] = 1;
	state[getIndex_on(16, 31, 1)] = 1;
	state[getIndex_occupied(44, 1)] = 1;
	state[getIndex_on(18, 35, 1)] = 1;
	state[getIndex_occupied(106, 1)] = 1;
	state[getIndex_on(20, 32, 1)] = 1;
	state[getIndex_occupied(63, 1)] = 1;
	state[getIndex_on(21, 33, 1)] = 1;
	state[getIndex_occupied(72, 1)] = 1;
	state[getIndex_on(22, 32, 1)] = 1;
	state[getIndex_occupied(57, 1)] = 1;
	state[getIndex_on(23, 33, 1)] = 1;
	state[getIndex_occupied(71, 1)] = 1;
	state[getIndex_on(27, 35, 1)] = 1;
	state[getIndex_occupied(100, 1)] = 1;
	state[getIndex_on(29, 31, 1)] = 1;
	state[getIndex_occupied(54, 1)] = 1;
	state[getIndex_on(30, 31, 1)] = 1;
	state[getIndex_occupied(53, 1)] = 1;
	state[getIndex_not_occupied(43, 1)] = 1;
	state[getIndex_not_occupied(42, 1)] = 1;
	state[getIndex_not_occupied(41, 1)] = 1;
	state[getIndex_not_occupied(47, 1)] = 1;
	state[getIndex_not_occupied(46, 1)] = 1;
	state[getIndex_not_occupied(45, 1)] = 1;
	state[getIndex_not_occupied(50, 1)] = 1;
	state[getIndex_not_occupied(49, 1)] = 1;
	state[getIndex_not_occupied(48, 1)] = 1;
	state[getIndex_not_occupied(52, 1)] = 1;
	state[getIndex_not_occupied(51, 1)] = 1;
	state[getIndex_not_occupied(56, 1)] = 1;
	state[getIndex_not_occupied(55, 1)] = 1;
	state[getIndex_not_occupied(61, 1)] = 1;
	state[getIndex_not_occupied(60, 1)] = 1;
	state[getIndex_not_occupied(59, 1)] = 1;
	state[getIndex_not_occupied(62, 1)] = 1;
	state[getIndex_not_occupied(66, 1)] = 1;
	state[getIndex_not_occupied(65, 1)] = 1;
	state[getIndex_not_occupied(68, 1)] = 1;
	state[getIndex_not_occupied(67, 1)] = 1;
	state[getIndex_not_occupied(70, 1)] = 1;
	state[getIndex_not_occupied(69, 1)] = 1;
	state[getIndex_not_occupied(75, 1)] = 1;
	state[getIndex_not_occupied(74, 1)] = 1;
	state[getIndex_not_occupied(73, 1)] = 1;
	state[getIndex_not_occupied(77, 1)] = 1;
	state[getIndex_not_occupied(76, 1)] = 1;
	state[getIndex_not_occupied(80, 1)] = 1;
	state[getIndex_not_occupied(79, 1)] = 1;
	state[getIndex_not_occupied(82, 1)] = 1;
	state[getIndex_not_occupied(81, 1)] = 1;
	state[getIndex_not_occupied(86, 1)] = 1;
	state[getIndex_not_occupied(85, 1)] = 1;
	state[getIndex_not_occupied(84, 1)] = 1;
	state[getIndex_not_occupied(83, 1)] = 1;
	state[getIndex_not_occupied(88, 1)] = 1;
	state[getIndex_not_occupied(87, 1)] = 1;
	state[getIndex_not_occupied(92, 1)] = 1;
	state[getIndex_not_occupied(91, 1)] = 1;
	state[getIndex_not_occupied(90, 1)] = 1;
	state[getIndex_not_occupied(94, 1)] = 1;
	state[getIndex_not_occupied(93, 1)] = 1;
	state[getIndex_not_occupied(96, 1)] = 1;
	state[getIndex_not_occupied(95, 1)] = 1;
	state[getIndex_not_occupied(99, 1)] = 1;
	state[getIndex_not_occupied(98, 1)] = 1;
	state[getIndex_not_occupied(97, 1)] = 1;
	state[getIndex_not_occupied(102, 1)] = 1;
	state[getIndex_not_occupied(101, 1)] = 1;
	state[getIndex_not_occupied(105, 1)] = 1;
	state[getIndex_not_occupied(104, 1)] = 1;
	state[getIndex_not_occupied(108, 1)] = 1;
	state[getIndex_not_occupied(107, 1)] = 1;
	state[getIndex_not_occupied(110, 1)] = 1;
	state[getIndex_not_occupied(109, 1)] = 1;
	state[getIndex_first(17, 36, 1)] = 1;
	state[getIndex_follow(11, 17, 1)] = 1;
	state[getIndex_last(11, 36, 1)] = 1;
	state[getIndex_first(12, 37, 1)] = 1;
	state[getIndex_follow(26, 12, 1)] = 1;
	state[getIndex_last(26, 37, 1)] = 1;
	state[getIndex_first(9, 38, 1)] = 1;
	state[getIndex_last(9, 38, 1)] = 1;
	state[getIndex_first(25, 39, 1)] = 1;
	state[getIndex_follow(24, 25, 1)] = 1;
	state[getIndex_follow(14, 24, 1)] = 1;
	state[getIndex_last(14, 39, 1)] = 1;
	state[getIndex_first(19, 40, 1)] = 1;
	state[getIndex_follow(15, 19, 1)] = 1;
	state[getIndex_follow(8, 15, 1)] = 1;
	state[getIndex_follow(28, 8, 1)] = 1;
	state[getIndex_last(28, 40, 1)] = 1;
	state[getIndex_not_unitary(36, 1)] = 1;
	state[getIndex_not_unitary(37, 1)] = 1;
	state[getIndex_unitary(38, 1)] = 1;
	state[getIndex_not_unitary(39, 1)] = 1;
	state[getIndex_not_unitary(40, 1)] = 1;
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
	state[getIndex_equals(64, 64, 1)] = 1;
	state[getIndex_equals(65, 65, 1)] = 1;
	state[getIndex_equals(66, 66, 1)] = 1;
	state[getIndex_equals(67, 67, 1)] = 1;
	state[getIndex_equals(68, 68, 1)] = 1;
	state[getIndex_equals(69, 69, 1)] = 1;
	state[getIndex_equals(70, 70, 1)] = 1;
	state[getIndex_equals(71, 71, 1)] = 1;
	state[getIndex_equals(72, 72, 1)] = 1;
	state[getIndex_equals(73, 73, 1)] = 1;
	state[getIndex_equals(74, 74, 1)] = 1;
	state[getIndex_equals(75, 75, 1)] = 1;
	state[getIndex_equals(76, 76, 1)] = 1;
	state[getIndex_equals(77, 77, 1)] = 1;
	state[getIndex_equals(78, 78, 1)] = 1;
	state[getIndex_equals(79, 79, 1)] = 1;
	state[getIndex_equals(80, 80, 1)] = 1;
	state[getIndex_equals(81, 81, 1)] = 1;
	state[getIndex_equals(82, 82, 1)] = 1;
	state[getIndex_equals(83, 83, 1)] = 1;
	state[getIndex_equals(84, 84, 1)] = 1;
	state[getIndex_equals(85, 85, 1)] = 1;
	state[getIndex_equals(86, 86, 1)] = 1;
	state[getIndex_equals(87, 87, 1)] = 1;
	state[getIndex_equals(88, 88, 1)] = 1;
	state[getIndex_equals(89, 89, 1)] = 1;
	state[getIndex_equals(90, 90, 1)] = 1;
	state[getIndex_equals(91, 91, 1)] = 1;
	state[getIndex_equals(92, 92, 1)] = 1;
	state[getIndex_equals(93, 93, 1)] = 1;
	state[getIndex_equals(94, 94, 1)] = 1;
	state[getIndex_equals(95, 95, 1)] = 1;
	state[getIndex_equals(96, 96, 1)] = 1;
	state[getIndex_equals(97, 97, 1)] = 1;
	state[getIndex_equals(98, 98, 1)] = 1;
	state[getIndex_equals(99, 99, 1)] = 1;
	state[getIndex_equals(100, 100, 1)] = 1;
	state[getIndex_equals(101, 101, 1)] = 1;
	state[getIndex_equals(102, 102, 1)] = 1;
	state[getIndex_equals(103, 103, 1)] = 1;
	state[getIndex_equals(104, 104, 1)] = 1;
	state[getIndex_equals(105, 105, 1)] = 1;
	state[getIndex_equals(106, 106, 1)] = 1;
	state[getIndex_equals(107, 107, 1)] = 1;
	state[getIndex_equals(108, 108, 1)] = 1;
	state[getIndex_equals(109, 109, 1)] = 1;
	state[getIndex_equals(110, 110, 1)] = 1;
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
				if(index1 >= 0 && index1 < 26){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 26){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 70){
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
						if(index3 >= 0 && index3 < 26){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 26){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 70){
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
				if(index1 >= 0 && index1 < 26){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 26){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 70){
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
						if(index3 >= 0 && index3 < 26){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 26){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 70){
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
				if(index1 >= 0 && index1 < 26){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 26){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 70){
											index8 = nondet_Int();
											if(index8 >= 0 && index8 < 70){
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
				if(index1 >= 0 && index1 < 26){
					index2 = nondet_Int();
					if(index2 >= 0 && index2 < 5){
						index3 = nondet_Int();
						if(index3 >= 0 && index3 < 5){
							index4 = nondet_Int();
							if(index4 >= 0 && index4 < 26){
								index5 = nondet_Int();
								if(index5 >= 0 && index5 < 5){
									index6 = nondet_Int();
									if(index6 >= 0 && index6 < 5){
										index7 = nondet_Int();
										if(index7 >= 0 && index7 < 70){
											index8 = nondet_Int();
											if(index8 >= 0 && index8 < 70){
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
		if((state[getIndex_on(7, 34, 0)] && state[getIndex_on(11, 33, 0)] && state[getIndex_on(14, 32, 0)] && state[getIndex_on(16, 33, 0)] && state[getIndex_on(26, 35, 0)] && state[getIndex_on(27, 31, 0)] && state[getIndex_normal(36, 0)] && state[getIndex_normal(37, 0)] && state[getIndex_normal(38, 0)] && state[getIndex_normal(39, 0)] && state[getIndex_normal(40, 0)])){
			__CPROVER_assert(1 == 0, "GOAL CHECKER: FAIL MEANS PLAN FOUND");
		}
	}
}
