#include "Component.h"
#include "../Math.h"
// ボックスコライダー
class ColliderComponent : public Component
{
public:
    ColliderComponent(Actor *owner, float width, float height);
    ~ColliderComponent();
    const Vector2 &GetCenterPosition() const;
    bool IsColliding(ColliderComponent &a, ColliderComponent &b);

private:
    float mWidth, mHeight;
};
