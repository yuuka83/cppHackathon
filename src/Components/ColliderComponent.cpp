#pragma once
#include "ColliderComponent.h"
#include "../Actors/Actor.h"
#include <iostream>

// コンストラクタ
ColliderComponent::ColliderComponent(Actor *owner, float width, float height)
    : Component(owner, 10), mWidth(width), mHeight(height)
{
}
ColliderComponent::~ColliderComponent()
{
}

// 中心位置を返す
const Vector2 &ColliderComponent::GetCenterPosition() const
{
    return mOwner->GetPosition();
}

bool IsColliding(ColliderComponent &a, ColliderComponent &b)
{
    float aLeft = a.GetCenterPosition().x - a.GetWidth() / 2;
    float aRight = a.GetCenterPosition().x + a.GetWidth() / 2;
    float bLeft = b.GetCenterPosition().x - b.GetWidth() / 2;
    float bRight = b.GetCenterPosition().x + b.GetWidth() / 2;
    float aTop = a.GetCenterPosition().y - a.GetHeight() / 2;
    float aBottom = a.GetCenterPosition().y + a.GetHeight() / 2;
    float bTop = b.GetCenterPosition().y - b.GetHeight() / 2;
    float bBottom = b.GetCenterPosition().y + b.GetHeight() / 2;
    // x軸とy軸で重なりがあるかチェック
    bool overlapX = aRight > bLeft && aLeft < bRight;
    bool overlapY = aBottom > bTop && aTop < bBottom;
    return overlapX && overlapY;
}