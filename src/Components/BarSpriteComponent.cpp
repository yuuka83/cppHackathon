#pragma once
#include "../Actors/Actor.h"
#include "BarSpriteComponent.h"
BarSpriteComponent::BarSpriteComponent(Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder), mRatio(1.0)
{
    firstPosX = mOwner->GetPosition().x - static_cast<int>(mTexWidth * mOwner->GetScale() * mRatio);
    firstPosY = mOwner->GetPosition().y - static_cast<int>(mTexHeight * mOwner->GetScale());
}
BarSpriteComponent::~BarSpriteComponent() {}
void BarSpriteComponent::SetRatio(int current, int max)
{
    mRatio = static_cast<float>(current) / static_cast<float>(max);
}
void BarSpriteComponent::Draw(SDL_Renderer *renderer)
{
    if (mTexture)
    {
        SDL_Rect r;
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale() * mRatio);
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
        r.x = firstPosX;
        r.y = firstPosY;

        SDL_RenderCopyEx(renderer,                                    // 描画操作の対象
                         mTexture,                                    // 描画するテクスチャ
                         nullptr,                                     // テクスチャのどの部分を描画するかを指定するソース矩形。nullptrを指定すると、テクスチャ全体が使用される。
                         &r, -Math::ToDegrees(mOwner->GetRotation()), // ラジアンから度数への変換 回転の角度
                         nullptr,                                     // 回転の中心点 nullptr:テクスチャの中心
                         SDL_FLIP_NONE);
    }
}