#pragma once

#include <collision/Collider.hpp>
#include <dynamics/DynamicsWorld.hpp>
#include <dynamics/Rigidbody.hpp>
#include <dynamics/Solver.hpp>

namespace spe
{

class RectangleEntity
{
  public:
    RectangleEntity(stw::DynamicsWorld &world, stw::Vector2 size, stw::Vector2 position);
    RectangleEntity(const RectangleEntity &) = delete;
    RectangleEntity(RectangleEntity &&) = default;
    ~RectangleEntity();

    void Draw() const;
    stw::Rigidbody *Rigidbody() const;

  private:
    stw::DynamicsWorld &m_World;

    std::unique_ptr<stw::Rigidbody> m_Body;
    std::unique_ptr<stw::AabbCollider> m_Collider;
};
} // namespace spe
