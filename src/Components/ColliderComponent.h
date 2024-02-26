#include "Component.h"
#include "../Math.h"
// 円コライダー
class ColliderComponent : public Component
{
public:
    ColliderComponent(class Actor *owner);
    ~ColliderComponent();
    const Vector2 &GetCenterPosition() const;
    virtual bool OnCollisionEnter(ColliderComponent &a, ColliderComponent &b);
    virtual bool OnCollisionStay(ColliderComponent &a, ColliderComponent &b);
    virtual bool OnCollisionExit(ColliderComponent &a, ColliderComponent &b);

private:
    bool mCollisionEnter;
};
