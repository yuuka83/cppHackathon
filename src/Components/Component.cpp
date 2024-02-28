#pragma once
#include "Component.h"
#include "../Actors/Actor.h"
#include "iostream"
Component::Component(Actor *owner, int updateOrder)
    : mOwner(owner), mUpdateOrder(updateOrder)
{
    // コンポーネントが生まれた瞬間にAddComponentする
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}