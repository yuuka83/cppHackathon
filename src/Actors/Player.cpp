#pragma once
#include <SDL.h>
#include "Player.h"
#include "../Components/AnimSpriteComponent.h"
#include "Enemy.h"
#include "../Game.h"
#include <iostream>

Player::Player(Game *game)
    : Actor(game), mPosx(0.0f), mPosy(0.0f) /*, mRightSpeed(0.0f), mDownSpeed(0.0f)*/
{
    /*
    AnimSpriteComponent *asc = new AnimSpriteComponent(this, 120);
    std::vector<SDL_Texture *> anims = {
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship01.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship02.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship03.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship04.png"),
    };
    asc->SetAnimTextures(anims);
    */
    SetScale(0.3f);
    SpriteComponent *sc = new SpriteComponent(this, 50);
    SDL_Texture *tex = game->GetTexture(GetGame()->GetAssetsPath() + "reticle.png");
    SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    sc->SetTexture(tex);
    mColliderComp = new ColliderComponent(this, sc->GetTexWidth() * GetScale(), sc->GetTexHeight() * GetScale());
}

void Player::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    Vector2 pos = GetPosition();
    pos.x = mPosx;
    pos.y = mPosy;
    SetPosition(pos);
}

void Player::ProcessInput(const uint8_t *state, bool mouseDown)
{
    SDL_Point mouse_position;

    // マウスイベント
    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
    if (mouse_position.x > GetGame()->GetWall()->GetPosition().x + 30)
    {
        mPosx = mouse_position.x;
        if (mouse_position.y > 110 && mouse_position.y < SCREEN_HEIGHT - 50)
        {
            mPosy = mouse_position.y;
        }
    }
    // マウス押し下していたら
    if (mouseDown == true)
    {
        // 敵と衝突しているか判定
        JudgeCollidingEnemy();
    }
}

void Player::JudgeCollidingEnemy()
{
    // std::cout << "実行" << std::endl;
    // 衝突検知
    for (auto enemy : GetGame()->GetEnemies())
    {
        // 敵と衝突していたら
        if (IsColliding(*mColliderComp, *(enemy->GetColliderComp())))
        {
            std::cout << "衝突" << std::endl;
            // enemyに50のダメージを与える
            enemy->Damage(50);
        }
    }
}