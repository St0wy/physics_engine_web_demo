#include "rectangle.hpp"
#include <raylib.h>

namespace spe
{

RectangleEntity::RectangleEntity(stw::DynamicsWorld &world, stw::Vector2 size, stw::Vector2 position)
    : m_World(world), m_Body(std::make_unique<stw::Rigidbody>()), m_Collider(std::make_unique<stw::AabbCollider>())
{
    m_Body->SetTransform(stw::Transform{position, {1.0f, 1.0f}, 0.0f});
    m_Body->SetTakesGravity(true);
    m_Body->SetIsKinematic(true);
    m_Body->SetRestitution(0.5f);
    m_Body->SetMass(10.0f);

    m_Collider->halfWidth = size.x / 2.0f;
    m_Collider->halfHeight = size.y / 2.0f;

    m_Body->SetCollider(m_Collider.get());
    m_World.AddRigidbody(m_Body.get());
}

RectangleEntity::~RectangleEntity()
{
    m_World.RemoveCollisionBody(Rigidbody());
}

void RectangleEntity::Draw() const
{
    auto rectanglePos = m_Body->Position();
    rectanglePos.x -= m_Collider->halfWidth;
    rectanglePos.y += m_Collider->halfHeight;
    Vector2 rectangleSize{m_Collider->halfWidth * 2.0f, m_Collider->halfHeight * 2.0f};
    DrawRectangleV({rectanglePos.x, -rectanglePos.y}, rectangleSize, MAROON);
}

stw::Rigidbody *RectangleEntity::Rigidbody() const
{
    return m_Body.get();
}
} // namespace spe