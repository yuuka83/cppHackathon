#include "Component.h"
#include "../Math.h"
#include "ColliderComponent.h"

class CircleColliderComponent : public ColliderComponent
{
public:
    CircleColliderComponent(class Actor *owner);
    ~CircleColliderComponent();
    const Vector2 &GetCenterPosition() const;
    bool OnCollisionEnter(ColliderComponent &a, ColliderComponent &b) override;
    bool OnCollisionStay(ColliderComponent &a, ColliderComponent &b) override;
    bool OnCollisionExit(ColliderComponent &a, ColliderComponent &b) override;

private:
    float mRadius; // 半径
    bool mCollisionEnter;

public:
    void SetRadius(float radius) { mRadius = radius; }
    const float GetRadius();
};