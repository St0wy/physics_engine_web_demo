#include "physics_engine_demo.hpp"

#include <iostream>

PhysicsEngineDemo::PhysicsEngineDemo(std::size_t windowWidth, std::size_t windowHeight, float zoom)
    : m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_Zoom(zoom),
      m_ImpulseSolver(std::make_unique<stw::ImpulseSolver>()),
      m_SmoothPositionSolver(std::make_unique<stw::SmoothPositionSolver>())
{
    InitWindow(m_WindowWidth, m_WindowHeight, "Physics engine demo !");

    m_Camera.target = Vector2{-(m_WindowWidth / 2.0f / m_Zoom), -(m_WindowHeight / 2.0f / m_Zoom)};
    m_Camera.zoom = m_Zoom;

    m_World.useSpacePartitioning = false;

    m_World.AddSolver(m_ImpulseSolver.get());
    m_World.AddSolver(m_SmoothPositionSolver.get());

    Circle c{m_World, 4.0f, stw::Vector2(0.0f, 0.0f)};
    m_Circles.push_back(std::move(c));
}

PhysicsEngineDemo::~PhysicsEngineDemo()
{
    CloseWindow();
}

void PhysicsEngineDemo::Loop()
{
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        m_World.Step(deltaTime);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(m_Camera);

        for (const auto &circles : m_Circles)
        {
            circles.Draw();
        }

        EndMode2D();

        DrawFPS(10, 10);

        EndDrawing();
    }
}
