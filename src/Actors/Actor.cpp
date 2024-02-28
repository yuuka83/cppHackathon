#pragma once
#include "Actor.h"
#include <vector>
#include "../Game.h"
#include "../Components/Component.h"
#include "../Math.h"
#include <algorithm>
#include <iostream>

Actor::Actor(Game *game)
    : mState(EActive), mPosition(Vector2::Zero), mScale(1.0f), mRotation(0.0f), mGame(game)
{
    // インスタンス化された際に自身を追加
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    // std::cout << mComponents.size() << std::endl;
    // mComponentsコンテナに含まれる各要素に対して繰り返し処理を行う
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component *component)
{

    int myOrder = component->getUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter)
    {
        // 自分の更新順よりmComponentsの更新順が小さかったら（mComponentsの自分の位置の１つ後を見つける）
        if (myOrder < (*iter)->getUpdateOrder())
        {
            break;
        }
    }

    // イテレータが指す位置の前に新しい要素が挿入される
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component *component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}