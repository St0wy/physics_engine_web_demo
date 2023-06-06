#pragma once

#include "circle.hpp"
#include <collision/Collider.hpp>
#include <cstddef>
#include <cstdint>
#include <dynamics/DynamicsWorld.hpp>
#include <dynamics/Rigidbody.hpp>
#include <dynamics/Solver.hpp>
#include <memory>
#include <raylib.h>
#include <vector>

class PhysicsEngineDemo
{
  public:
    PhysicsEngineDemo(std::size_t windowWidth, std::size_t windowHeight, float zoom = 4.0f);
    ~PhysicsEngineDemo();

    void Loop();

  private:
    std::size_t m_WindowWidth;
    std::size_t m_WindowHeight;
    float m_Zoom;

    Camera2D m_Camera{};

    stw::DynamicsWorld m_World{};

    std::unique_ptr<stw::ImpulseSolver> m_ImpulseSolver;
    std::unique_ptr<stw::SmoothPositionSolver> m_SmoothPositionSolver;

    std::vector<Circle> m_Circles{};
};