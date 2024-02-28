#pragma once
#include "Actor.h"
#include "../Components/ColliderComponent.h"

class Player : public Actor
{
public:
    Player(class Game *game);
    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t *state, bool mouseDown);
    void JudgeCollidingEnemy();

private:
    float mPosx;
    float mPosy;
    ColliderComponent *mColliderComp;
};