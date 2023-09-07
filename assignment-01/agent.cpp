#include "framework/charles.h"
#include "assignments/assignment1.h"

void test_agent()
{
    // Please ignore this part. It's really funny to watch at max speed
    for (int i = 0; i < 420; i++) {
        step();
        turn_right();
    }
}

void string_agent()
{
    /* Charles picks up the ball and then moves forward
    After this, he checks if he's in front of a wall
    If he is, he turns right to prevent hitting it
    */
    while (on_ball())
    { // keeps the program running
        get_ball();
        step();
        if (in_front_of_wall())
        {
            turn_right();
        }
    }
}

void turn_180()
{
    // turns 180 degrees by making two right turns
    turn_right();
    turn_right();
}

void try_get_ball()
{
    // Saves a lot of repetitive safe-checks
    if (on_ball())
    {
        get_ball();
    }
}

void safe_step()
{
    // Not strictly necessary for the examples given here, but useful for some edge-cases, so still used
    if (!in_front_of_wall())
    {
        step();
    }
}

void go_to_wall()
{ // Walks Charles to the next wall. Incredibly useful
    while (!in_front_of_wall())
        step();
}

void clear_line_back()
{
    /* Gets called when Charles detects he's at the end
    of a line, either through clear_line_front or clear_line_double
    It simply runs him back to the east while collecting the balls he finds along the way
    */
    turn_left();
    safe_step();
    while (!on_ball() && !in_front_of_wall())
    {
        step();
    }
    while (!in_front_of_wall())
    { // Walk back to the east wall while picking up balls
        get_ball();
        step();
    }
    turn_right();
    step();
}

void clear_line_double()
{
    /* This function gets called by clear_line_front()
    when Charles detects a ball after finishing a line and going down
    this means that he is currently in a line and should go to the end to clear it
    which is exactly what this function does: it goes to the end
    and then calls clear_line_back() to clear the line
    */
    turn_right();
    safe_step();
    while (on_ball())
    { // Go to the west end of the line
        safe_step();
    }
    turn_left();
    clear_line_back(); // Returns Charles to the east wall while picking up balls
}

void clear_line_front()
{
    /*  Clears a single line from east to west
    After this, it steps down a line and determines
    if it can go straight back to east or if it
    needs to go west to reach the end of that line
    */
    turn_right();
    safe_step();
    while (on_ball())
    { // Clear the line out to the west end
        get_ball();
        safe_step();
    }
    turn_left();
    step();
    if (on_ball())
    { // This means it's in the line of balls, and should go west
        clear_line_double();
    }
    else
    { // This means it can go directly east, and will find a line there
        clear_line_back();
    }
}

void chaos_agent()
{

    /* Quite a complicated function, it will first go to the top right corner
    And from there it'll go down one line at a time and pick up balls along the way
    If possible, on the next line it will go back to the east side picking up balls
    Otherwise, it will go to the west side of the line and then go back to the east
    (This is all handled in the 3 clear_line_x functions)
    After it reaches the east side without finding a ball at the end it will return
    picking up the final line of balls along the way
    */
    while (!in_front_of_wall())
    { // Walk to east side, picking up balls along the way
        try_get_ball();
        step();
    }
    try_get_ball();
    turn_right();
    step();
    while (on_ball())
    { // Most of the complicated logic is handled in the functions
        clear_line_front();
    }
    turn_180();
    step();
    while (!in_front_of_wall())
    { // Go back to north-east corner, picking up balls along the way
        try_get_ball();
        step();
    }
    turn_left();
    go_to_wall(); // Go to the north-west corner
    turn_180(); // Turn to face east
}

/* Code and comments above were mainly written by Sybren
Everything below was written by Jonar
(We decided to split tasks because it was easier with collaborating)
*/

void step_to_block_corner()
{ // Step to the corner of the block putting balls on every space along the way
    while (in_front_of_wall())
    {
        turn_left(); // Turn away from wall
        put_ball();
        step();
        turn_right(); // Turn to wall for loop check
    }
}

void block_agent()
{
    while (!on_ball()) // Step until on ball
        step();
    turn_right(); // Face block and step to the block
    go_to_wall();
    while (!on_ball())
    { // Do this until on a ball again
        step_to_block_corner();
        put_ball(); // Put ball on corner and go around corner
        step();
        turn_right(); // Face wall again for move loop
    }
    turn_180();     // Turn around to face other wall, charles is facing the block at this point
    go_to_wall(); // Step to the other wall
    turn_left();    // Turn to the northwest corner
    go_to_wall(); // Step to the corner
    turn_180();     // Face east
}
