#pragma once
#include "GuardWall.h"
#include "../Game.h"
#include "../Scenes/EndScene.h"

GuardWall::GuardWall(Game *game)
    : Actor(game), mWallHp(100)
{
    SetScale(1.2f); // 2倍の大きさ
    SpriteComponent *sc = new SpriteComponent(this, 10);
    SDL_Texture *tex = game->GetTexture(GetGame()->GetAssetsPath() + "Wall.png");
    SetPosition(Vector2(120, SCREEN_HEIGHT / 2));
    sc->SetTexture(tex);
    mColliderComp = new ColliderComponent(this, sc->GetTexWidth() * GetScale(), sc->GetTexHeight() * GetScale());
    mWallMaxHp = 100;
    mWallHp = 100;
}
void GuardWall::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}

void GuardWall::Damage(int damage)
{
    if (mWallHp - damage > 0)
    {
        mWallHp -= damage;
        GetGame()->GetWallHpBar()->GetBsc()->SetRatio(mWallHp, mWallMaxHp);
    }
    else
    {
        mWallHp = 0;
        GetGame()->GetWallHpBar()->GetBsc()->SetRatio(mWallHp, mWallMaxHp);
        // SetState(EDead);
        // 終了シーンへ
        GetGame()->SetNextScene(new EndScene(GetGame()));
    }
}