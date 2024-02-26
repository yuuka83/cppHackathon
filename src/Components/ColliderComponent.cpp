#include "ColliderComponent.h"
#include "../Actors/Actor.h"
#include <iostream>

// コンストラクタ
ColliderComponent::ColliderComponent(Actor *owner, float width, float height)
    : Component(owner, 10), mWidth(width), mHeight(height)
{
}
// 中心位置を返す
const Vector2 &ColliderComponent::GetCenterPosition() const
{
    return mOwner->GetPosition();
}

bool ColliderComponent::IsColliding(ColliderComponent &a, ColliderComponent &b)
{
    // x軸とy軸で重なりがあるかチェック
    // aの左線の座標がbの左線の座標よりも小さいかつaの右線の座標がbの右線の座標よりも大きい
    bool overlapX = a.GetCenterPosition().x - a.mWidth / 2 < b.GetCenterPosition().x - b.mWidth / 2 &&
                    a.GetCenterPosition().x + a.mWidth / 2 > b.GetCenterPosition().x + b.mWidth / 2;
    bool overlapY = a.GetCenterPosition().y - a.mHeight / 2 < b.GetCenterPosition().y - b.mHeight / 2 &&
                    a.GetCenterPosition().y + a.mHeight / 2 > b.GetCenterPosition().y + b.mHeight / 2;
    return overlapX && overlapY;
}