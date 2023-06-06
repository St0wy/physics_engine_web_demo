#pragma once

#include <dynamics/DynamicsWorld.hpp>
#include <dynamics/Rigidbody.hpp>
#include <dynamics/Solver.hpp>

class Circle
{
  public:
    Circle(stw::DynamicsWorld &world, float radius, stw::Vector2 position);
    Circle(const Circle &) = delete;
    Circle(Circle &&) = default;
    ~Circle();

    void Draw() const;
    stw::Rigidbody *Rigidbody() const;

  private:
    stw::DynamicsWorld &m_World;

    std::unique_ptr<stw::Rigidbody> m_Body;
    std::unique_ptr<stw::CircleCollider> m_Collider;
};