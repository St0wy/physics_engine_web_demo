#include "physics_engine_demo.hpp"

#include <iostream>

namespace spe
{
PhysicsEngineDemo::PhysicsEngineDemo(std::size_t windowWidth, std::size_t windowHeight, float zoom)
    : m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_Zoom(zoom),
      m_ImpulseSolver(std::make_unique<stw::ImpulseSolver>()),
      m_SmoothPositionSolver(std::make_unique<stw::SmoothPositionSolver>())
{
    InitWindow(m_WindowWidth, m_WindowHeight, "Physics engine demo !");

    m_Camera.target = Vector2{-(m_WindowWidth / 2.0f / m_Zoom), -(m_WindowHeight / 2.0f / m_Zoom)};
    m_Camera.zoom = m_Zoom;

    m_World.useSpacePartitioning = false;
    // TODO: Add broadphase grid

    m_World.AddSolver(m_ImpulseSolver.get());
    m_World.AddSolver(m_SmoothPositionSolver.get());

    CircleEntity c{m_World, 1.0f, stw::Vector2(0.0f, 0.0f)};
    m_Circles.push_back(std::move(c));

    RectangleEntity r{m_World, stw::Vector2(40.0f, 2.0f), stw::Vector2(0.0f, -5.0f)};
    auto *rb = r.Rigidbody();
    rb->SetIsKinematic(false);
    rb->SetTakesGravity(false);
    rb->SetMass(std::numeric_limits<float>::max());
    m_Rectangles.push_back(std::move(r));
}

PhysicsEngineDemo::~PhysicsEngineDemo()
{
    CloseWindow();
}

stw::Vector2 PhysicsEngineDemo::ToWorldSpace(Vector2 screenSpacePos)
{
    return stw::Vector2((screenSpacePos.x - (m_WindowWidth / 2.0f)) / m_Zoom,
                        -(screenSpacePos.y - (m_WindowHeight / 2.0f)) / m_Zoom);
}

void PhysicsEngineDemo::HandleSpawn()
{
    if (IsMouseButtonPressed(0))
    {
        auto mousePosScreen = GetMousePosition();
        auto mousePos = ToWorldSpace({mousePosScreen.x, mousePosScreen.y});
        std::cout << "Prout\n" << mousePos.x << "  " << mousePos.y << "\n";
        CircleEntity c{m_World, 1.0f, mousePos};
        m_Circles.push_back(std::move(c));
    }

    // TODO: Add rectangle creation
}

void PhysicsEngineDemo::Loop()
{
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // TODO : Adjust this once broadphase is done
        constexpr std::size_t substebCount = 8;
        for (std::size_t i = 0; i < substebCount; i++)
        {

            m_World.Step(deltaTime / substebCount);
        }

        HandleSpawn();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(m_Camera);

        for (const auto &circles : m_Circles)
        {
            circles.Draw();
        }

        for (const auto &rectangles : m_Rectangles)
        {
            rectangles.Draw();
        }

        EndMode2D();

        DrawFPS(10, 10);

        EndDrawing();
    }
}
} // namespace spe
