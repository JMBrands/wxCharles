#include "framework/charles.h"
#include "assignments/assignment1.h"

void test_agent() {

}

void string_agent() {
    while (on_ball()) { //keeps the program running
        // Charles picks up the ball and then moves forward
        // After this, he checks if he's in front of a wall
        // If he is, he turns right to prevent hitting it
        get_ball(); 
        step();
        if (in_front_of_wall()) {
            turn_right();
        }
    }
}

void turn_180() { // turns 180 degrees by making two right turns
    turn_right();
    turn_right();
}

void try_get_ball() {
    // Saves a lot of repetitive safe-checks
    if (on_ball()) {
        get_ball();
    }
}

void safe_step() {
    // Another incredibly useful function. Not necessary for the examples, but useful for some edge-cases
    if (!in_front_of_wall()) {
        step();
    }
}

void clear_line_back() {
    turn_left();
    safe_step();
    while (!in_front_of_wall()) {
        try_get_ball();
        step();
    }
    turn_right();
}

void clear_line_double() {
    turn_right();
    safe_step();
    while (on_ball()) {
        safe_step();
    }
    turn_left();
    clear_line_back();
}

void clear_line_front() {
    // Clears a single line. Useful.
    turn_right();
    safe_step();
    while(on_ball()) {
        get_ball();
        safe_step();
    }
    turn_left();
    step();
    if (on_ball()) {
        clear_line_double();
    }
    else {
        clear_line_back();
    }
}

void chaos_agent() {
    // Walks to the east side,
    // and from there walks to the west on each y-coordinate
    // picking up balls along the way
    while(!in_front_of_wall()) {
        try_get_ball();
        step();
    }
    try_get_ball();
    turn_right();
    step();
    while(on_ball()) {
        clear_line_front();
    }
    turn_180();
    step();
    while(on_ball()) {
        get_ball();
        step();
    }
    turn_left();
    while(!in_front_of_wall()) {
        step();
    }
    turn_180();
}

void step_to_wall() { // step to wall
    while (!in_front_of_wall())
        step();
}

void step_to_block_corner() { // step to the corner of the block putting balls on every space along the way
    while(in_front_of_wall()) {
        turn_left(); // turn away from wall
        put_ball();
        step();
        turn_right(); // turn to wall for loop check
    }
}

void block_agent() {
    while (!on_ball()) // step until on ball
        step();
    turn_right(); // face block and step to the block
    step_to_wall();
    while (!on_ball()) { // do this until on a ball again
        step_to_block_corner();
        put_ball(); // put ball on corner and go around corner
        step();
        turn_right(); // face wall again for move loop
    }
    turn_180(); // turn around to face other wall, charles is facing the block at this point
    step_to_wall(); // step to the other wall
    turn_left(); // turn to the northwest corner
    step_to_wall(); // step to the corner
    turn_180(); // face east
}
