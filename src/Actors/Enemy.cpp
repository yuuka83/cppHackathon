#pragma once
#include "Enemy.h"
#include "../Components/AnimSpriteComponent.h"
#include "../Game.h"
#include <iostream>
Enemy::Enemy(Game *game)
    : Actor(game), mEnemySpeed(100), mAttackTimer(0), mAttackTime(3)
{
    game->AddEnemy(this);
    AnimSpriteComponent *asc = new AnimSpriteComponent(this);
    // 画像の登録
    std::vector<SDL_Texture *> anims = {
        game->GetTexture(GetGame()->GetAssetsPath() + "skeleton09.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "skeleton10.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "skeleton11.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "skeleton12.png")};
    mEnemyMaxHp = 100;
    mEnemyHp = 100;
    mEnemyState = Walk;
    int num = std::rand() % (SCREEN_HEIGHT - 200) + 110; // 乱数を出す
    Vector2 pos = Vector2(SCREEN_WIDTH, num);
    SetPosition(pos); // 初期位置の決定
    asc->SetAnimTextures(anims);
    asc->SetAnimFPS(10.0f);
    SetScale(1.5f);
    mColliderComp = new ColliderComponent(this, asc->GetTexWidth(), asc->GetTexHeight());
}

Enemy::~Enemy()
{
    GetGame()->RemoveEnemy(this);
}

void Enemy::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    Vector2 pos = GetPosition();
    // 壁に衝突してなければ進み続ける
    if (IsColliding(*mColliderComp, *(GetGame()->GetWall()->GetColliderComponent())))
    {
        mAttackTimer += deltaTime;
        if (mAttackTimer > mAttackTime)
        {
            mAttackTimer = 0;
            // 壁にダメージを与える
            GetGame()->GetWall()->Damage(20);
        }
    }
    else
    {
        pos.x -= mEnemySpeed * deltaTime;
        SetPosition(pos);
    }
}

void Enemy::Damage(int damage)
{
    if (mEnemyHp - damage > 0)
    {
        mEnemyHp -= damage;
    }
    else
    {
        mEnemyHp = 0;
        SetState(EDead);
    }
}
