#include "physics_engine_demo.hpp"

#include <iostream>

PhysicsEngineDemo::PhysicsEngineDemo(std::size_t windowWidth, std::size_t windowHeight, float zoom)
    : m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_Zoom(zoom),
      m_ImpulseSolver(std::make_unique<stw::ImpulseSolver>()),
      m_SmoothPositionSolder(std::make_unique<stw::SmoothPositionSolver>()),
      m_BallBody(std::make_unique<stw::Rigidbody>()), m_BallCollider(std::make_unique<stw::CircleCollider>(4.0f))
{
    InitWindow(m_WindowWidth, m_WindowHeight, "Physics engine demo !");

    m_Camera.target = Vector2{-(m_WindowWidth / 2.0f / m_Zoom), -(m_WindowHeight / 2.0f / m_Zoom)};
    m_Camera.zoom = m_Zoom;

    m_World.useSpacePartitioning = false;

    m_World.AddSolver(m_ImpulseSolver.get());
    m_World.AddSolver(m_SmoothPositionSolder.get());

    m_BallBody->SetTransform(stw::Transform{{0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f});
    m_BallBody->SetTakesGravity(true);
    m_BallBody->SetIsKinematic(true);
    m_BallBody->SetRestitution(0.5f);
    m_BallBody->SetMass(10.0f);

    m_BallBody->SetCollider(m_BallCollider.get());
    m_World.AddRigidbody(m_BallBody.get());
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

        auto ballPos = m_BallBody->Position();
        DrawCircleV({ballPos.x, -ballPos.y}, m_BallCollider->radius, MAROON);

        EndMode2D();

        DrawFPS(10, 10);

        EndDrawing();
    }
}
