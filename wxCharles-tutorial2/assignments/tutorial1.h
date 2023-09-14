#pragma once

#include "util/include_guard.h"
#include "util/common_worldgen.h"
#include "../framework/assignment.h"

#include <algorithm>
#include <vector>

// Function declarations for agents implemented by student.
extern void test_agent();
extern void structure_agent();

class StructureExercise : public RandomExercise {
public:
    StructureExercise(std::string name, std::string description, std::string category)
        : RandomExercise(name, description, 0x457245, category) {}

protected:
    World Create() override {
        int width = NextRandomInt(25, 30);
        int height = NextRandomInt(10, 12);

        World world(width, height * 2 + 2, {1, 1}, DIR_SOUTH);
        EncloseInWalls(world);
        world.SetTileTypeAt({1, height+1}, TileType::Wall);

        std::vector<int> balls;

        while((int)balls.size() != height + 1) {
            int x = NextRandomInt(2, width - 2);

            if(std::find(balls.begin(), balls.end(), x) == balls.end()) {
                balls.push_back(x);
            }
        }

        for(int i = 0; i < height - 1; ++i) {
            world.SetBallAt({balls[i], i+1}, true);
            world.SetBallAt({balls[i], height + NextRandomInt(2, height - 2)}, true);
        }

        return world;
    }
};

class Tutorial1Assignment : public Assignment {
public:
    Tutorial1Assignment() {
        AddAgent("Test\tCtrl+0", "Test agent", "", test_agent);
        
        AddExercise(
            new StructureExercise("Code Structure\tAlt+1", "Code Structure exercise", "Tutorial 1")
        )->AttachAgent(AddAgent("Code Structure\tCtrl+1", "Agent for the code structure exercise", "Tutorial 1", structure_agent));
    }
};

CREATE_ASSIGNMENT(Tutorial1Assignment)