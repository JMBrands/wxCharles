#include "framework/charles.h"
#include "assignments/tutorial1.h"

// ****************************************
// TutEx1: Improve the structure of the
// code shown below through making use of
// functions with descriptive names.
// The algorithm already works; your task
// is to make the code easier to understand
// for other programmers. Also introduce
// short comments if need be. Adding 'mark'
// commands in the code at key points may
// also make it easier to understand for
// readers. See the Charles user manual.
// ****************************************

void step_to_ball() {
    while (!on_ball()) 
        step();
}

void step_to_wall() {
    while (!in_front_of_wall())
        step();
}

void turn_180() {
    turn_left();
    turn_left();
}

void clean_balls() {
    while(!in_front_of_wall()) {
        clean_row();
        move_to_next_row();
    }
}

void move_to_next_row() {
    turn_left();
    step_to_wall();
    turn_left();
    step();
}

void clean_row() {
    turn_left();
    step_to_ball();
    turn_right();
    step();
    step_to_ball();
    get_ball();
    turn_180();
    step_to_ball();
    get_ball();
}

void step_to_start() { 
    turn_180();
    step_to_wall();
    turn_right();
}

void structure_agent() {
    clean_balls();
    step_to_start();
}

void test_agent() {}