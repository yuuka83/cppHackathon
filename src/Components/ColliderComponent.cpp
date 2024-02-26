#include "ColliderComponent.h"
#include "../Actors/Actor.h"
#include <iostream>

const Vector2 &ColliderComponent::GetCenterPosition() const
{
}

// 衝突し始めを検知
bool ColliderComponent::OnCollisionEnter(ColliderComponent &a, ColliderComponent &b)
{
}
// 衝突している時を検知
bool ColliderComponent::OnCollisionStay(ColliderComponent &a, ColliderComponent &b)
{
}

// 衝突し終わった時を検知
bool ColliderComponent::OnCollisionExit(ColliderComponent &a, ColliderComponent &b)
{
}