#include "framework/charles.h"
#include "assignments/assignment1.h"

void test_agent() {

}

void string_agent() {
    while (on_ball()) {
        get_ball();
        step();
        if (in_front_of_wall()) {
            turn_right();
        }
    }
}

void chaos_agent() {

}

void block_agent() {

}
