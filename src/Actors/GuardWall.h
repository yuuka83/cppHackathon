#pragma once
#include "Actor.h"
#include "SDL.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ColliderComponent.h"

class GuardWall : public Actor
{
public:
    GuardWall(class Game *game);
    void UpdateActor(float deltaTime) override;
    void Damage(int damage);

private:
    int mWallMaxHp;
    int mWallHp;
    int damage;
    ColliderComponent *mColliderComp;

public: // ゲッター・セッター
    ColliderComponent *GetColliderComponent() { return mColliderComp; }
};