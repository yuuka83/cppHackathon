#pragma once
#include "Component.h"
#include "../Math.h"
// ボックスコライダー
class ColliderComponent : public Component
{
public:
    ColliderComponent(Actor *owner, float width, float height);
    ~ColliderComponent();
    const Vector2 &GetCenterPosition() const;

private:
    float mWidth, mHeight;

public:
    float GetWidth() { return mWidth; }
    float GetHeight() { return mHeight; }
};

bool IsColliding(ColliderComponent &a, ColliderComponent &b);