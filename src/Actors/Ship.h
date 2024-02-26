#pragma once
#include "Actor.h"
class Ship : public Actor
{
public:
    Ship(class Game *game);
    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t *state, SDL_Point mouse_position);
    // float GetRightSpeed() const { return mRightSpeed; }
    // float GetDownSpeed() const { return mDownSpeed; }

private:
    float mPosx;
    float mPosy;
};