
#include "physics_engine_demo.hpp"
#include <iostream>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    PhysicsEngineDemo demo{screenWidth, screenHeight};
    demo.Loop();
}