#include "circle.hpp"

#include <raylib.h>
namespace spe
{
CircleEntity::CircleEntity(stw::DynamicsWorld &world, float radius, stw::Vector2 position)
    : m_World(world), m_Body(std::make_unique<stw::Rigidbody>()), m_Collider(std::make_unique<stw::CircleCollider>())
{
    m_Body->SetTransform(stw::Transform{position, {1.0f, 1.0f}, 0.0f});
    m_Body->SetTakesGravity(true);
    m_Body->SetIsKinematic(true);
    m_Body->SetRestitution(0.5f);
    m_Body->SetMass(10.0f);

    m_Collider->radius = radius;

    m_Body->SetCollider(m_Collider.get());
    m_World.AddRigidbody(m_Body.get());
}

CircleEntity::~CircleEntity()
{
    m_World.RemoveCollisionBody(Rigidbody());
}

void CircleEntity::Draw() const
{
    auto ballPos = m_Body->Position();
    DrawCircleV({ballPos.x, -ballPos.y}, m_Collider->radius, MAROON);
}

stw::Rigidbody *CircleEntity::Rigidbody() const
{
    return m_Body.get();
}
} // namespace spe
