#pragma once

#include <dynamics/DynamicsWorld.hpp>
#include <dynamics/Rigidbody.hpp>
#include <dynamics/Solver.hpp>

namespace spe
{
class CircleEntity
{
  public:
    CircleEntity(stw::DynamicsWorld &world, float radius, stw::Vector2 position);
    CircleEntity(const CircleEntity &) = delete;
    CircleEntity(CircleEntity &&) = default;
    ~CircleEntity();

    void Draw() const;
    stw::Rigidbody *Rigidbody() const;

  private:
    stw::DynamicsWorld &m_World;

    std::unique_ptr<stw::Rigidbody> m_Body;
    std::unique_ptr<stw::CircleCollider> m_Collider;
};
} // namespace spe
