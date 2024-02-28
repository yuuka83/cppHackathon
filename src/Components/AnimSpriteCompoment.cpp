#pragma once
#include "AnimSpriteComponent.h"
#include "../Math.h"
#include <iostream>

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder), mCurrentFrame(0.0f), mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);
    // mAnimTexturesのサイズが0より大きかったら
    if (mAnimTextures.size() > 0)
    {
        // 現在のフレームをmAnimFPSをもとに更新
        mCurrentFrame += mAnimFPS * deltaTime;
        // 現在のフレームがテクスチャのサイズより大きかったら
        while (mCurrentFrame >= mAnimTextures.size())
        {
            // 現在のフレームから最初のフレームに戻る
            mCurrentFrame -= mAnimTextures.size();
        }
        // 現在のテクスチャをセットする
        SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
        // std::cout << mCurrentFrame << std::endl;
    }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture *> &textures)
{
    // アニメーションとして使用するテクスチャのリストを更新
    mAnimTextures = textures;
    // アニメーションテクスチャの存在チェック
    if (mAnimTextures.size() > 0)
    {
        // 現在のアニメーションフレームを0に設定
        mCurrentFrame = 0.0f;
        // アニメーションの最初のテクスチャをアクティブなテクスチャとして設定
        SetTexture(mAnimTextures[0]);
    }
}