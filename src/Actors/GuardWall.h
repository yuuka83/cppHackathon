#pragma once
#include "Actor.h"

class GuardWall : public Actor
{
public:
    GuardWall(class Game *game);
    ~GuardWall();
    void UpdateActor(float deltaTime) override;

private:
    int mWallHp;
    int damage;
};