#include "framework/charles.h"
#include "assignments/assignment2.h"

void turn_around() {
    // Used a LOT
    // Extremely useful
    turn_left();
    turn_left();
}

void step_back() {
    // Used once or twice
    // Enough times to make it useful
    turn_around();
    step();
    turn_around();
}

void test_agent() {
    // Looks funny lol
    for (int i = 0; i < 1000000; i ++) {
        turn_right();
    }
}

void step_to_wall() {
    // Used in some things
    // Very nice
    while (!in_front_of_wall()) {
        step();
    }
}

void step_to_ball() {
    // Used in the bonus assignment
    while (!on_ball()) {
        step();
    }
}

void path_right_step() {
    /*
    If Charles cannot find anything to the right
    it means he is at the end of the path
    He will pick up the ball to break out of the control loop
    */
    if (!in_front_of_wall()) {
        step();
        if (!on_ball()) {
            step_back();
            get_ball();
        }
    }
    else {
        get_ball();
    }
}

void path_left_step() {
    /*
    After Charles has failed at walking forward
    He will try left (nearly the same code)
    */
    if (in_front_of_wall()) {
        turn_around();
        path_right_step();
    }
    else {
        step();
        if (!on_ball()) {
            turn_around();
            step();
            path_right_step();
        }
    }
}

void path_front_step() {
    /* 
    Charles will first try to walk forward
    if his way is blocked by a wall or if there's no ball there
    he will try to go left instead 
    */
    if (in_front_of_wall()) {
        turn_left();
        path_left_step();
    }
    else {
        step();
        if(!on_ball()) {
            turn_around();
            step();
            turn_right();
            path_left_step();
        }
    }
}

void path_agent() {
    while(on_ball()) { // The functions handle most of the logic
        path_front_step();
    }
    put_ball(); // If Charles detects the end of the line, he will remove the ball to break free from the loop
    while(!north()) { // Faces charles east
        turn_left();
    }
    turn_right();
}


void single_stalag() {
    /*
    this function makes a single stalagmite/stalagtite by stepping and dropping balls until hitting a wall,
    then turning around and going back to the outer wall
    */
    turn_right();
    while(!in_front_of_wall()) {
        put_ball();
        step();
    }
    put_ball();
    turn_around();
    step_to_wall();
    turn_right();
}

// NOTE: this agent is executed twice in a row. See the PDF for more details.
void cave_agent() {
    step(); // The east/west walls must stay clear
    while (!in_front_of_wall()) { // The main loop
        single_stalag();
        step();
    }
    turn_right(); // Positions Charles to be ready fo the next iteration
    step_to_wall();
    turn_right();
    
}

void find_center_line() {
    step_to_wall(); // Walks Charles to the wall to put down the second ball
    put_ball();
    turn_around();
    step();
    while (!on_ball()) { // Makes Charles bounce between the balls
        step_to_ball();
        turn_around();
        step();
        put_ball();
        step();
    }
    turn_around();
    step();
}

void find_center_agent() {
    /*
    Charles first walks to the end points to put balls there
    and then bounces between the balls to find the middle
    */
    put_ball(); // PLaces first ball on X-axis
    find_center_line();
    turn_left();
    find_center_line(); // First ball on Y-axis was already placed
    turn_right(); // Turns Charles to face the east
    clean_up_agent(); // Just extra fancyness

}

void clear_to_wall() {
    // Very useful for cleaning up
    while(!in_front_of_wall()) {
        step();
        get_ball();
    }
}
void clear_line() {
    /*
    Clears a full line by clearing to one wall, 
    returning to the marker/center ball, and clearing to the other wall
    */
    turn_right();
    clear_to_wall();
    turn_around();
    step_to_ball();
    clear_to_wall();
}

void clean_up_agent() {
    /*
    Charles first clears the Y-axis except for a marker ball and the center ball
    Then the X-axis except for the marker ball present there
    Then he finds the correct X coordinate by the marker ball
    and the Y coordinate by the center ball
    */
    clear_line(); // Clears the Y axis
    put_ball(); // Puts down the marker ball
    clear_line(); // Clears the X axis
    turn_around(); // Returns to the marker ball
    step_to_ball();
    get_ball(); // Removes the marker ball
    turn_right(); // Returns to the center ball
    step_to_ball();
    turn_left(); // Faces east
    
}
