#pragma once
#include "SpriteComponent.h"
#include "../Actors/Actor.h"
#include "../Game.h"

SpriteComponent::SpriteComponent(Actor *owner, int drawOrder)
    : Component(owner), mTexture(nullptr), mDrawOrder(drawOrder), mTexHeight(0), mTexWidth(0)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer *renderer)
{
    if (mTexture)
    {
        SDL_Rect r;
        // ownerのスケールに合わせたスケールにする
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

        r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2); // 左隅のx
        r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2); // 左隅のy

        SDL_RenderCopyEx(renderer,                                    // 描画操作の対象
                         mTexture,                                    // 描画するテクスチャ
                         nullptr,                                     // テクスチャのどの部分を描画するかを指定するソース矩形。nullptrを指定すると、テクスチャ全体が使用される。
                         &r, -Math::ToDegrees(mOwner->GetRotation()), // ラジアンから度数への変換 回転の角度
                         nullptr,                                     // 回転の中心点 nullptr:テクスチャの中心
                         SDL_FLIP_NONE);                              // テクスチャの反転を行わないことを指定
    }
}

// 新しいSDL_Textureを設定し、そのテクスチャの幅と高さを取得する
// テクスチャのフォーマット、アクセスモード、幅、高さを取得できる
void SpriteComponent::SetTexture(SDL_Texture *texture)
{
    mTexture = texture;
    // 指定されたテクスチャの情報を取得
    SDL_QueryTexture(texture,
                     nullptr,      // フォーマット 今はいらないのでnull
                     nullptr,      // アクセスモード　今はいらないのでnull
                     &mTexWidth,   // 幅をmTexWidthに格納
                     &mTexHeight); // 高さをmTexHeightに格納
}