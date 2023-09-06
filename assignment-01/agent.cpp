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

void try_get_ball() {
    // Saves a lot of repetitive safe-checks
    if (on_ball()) {
        get_ball();
    }
}

void safe_step() {
    // Another incredibly useful function. Not necessary for the examples, but useful for some edge-cases
    if (!in_front_of_wall) {
        step();
    }
}

void clear_line_back() {
    turn_left();
    safe_step();
    while (!in_front_of_wall()) {
        try_get_ball()
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
    turn_left();
    turn_left();
    step();
    while(on_ball()) {
        get_ball();
        step();
    }
    turn_left();
    while(!in_front_of_wall()) {
        step();
    }
    turn_left();
    turn_left();
}

void block_agent() {

}
