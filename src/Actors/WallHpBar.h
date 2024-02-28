#pragma once
#include "Actor.h"
#include "../Components/BarSpriteComponent.h"
class WallHpBar : public Actor
{
public:
    WallHpBar(class Game *game);
    void UpdateActor(float deltaTime) override;

private:
    BarSpriteComponent *mBsc;

public:
    BarSpriteComponent *GetBsc() { return mBsc; }
};