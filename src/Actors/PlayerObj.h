#pragma once
#include "Actor.h"
#include "SDL.h"
#include "../Components/SpriteComponent.h"

class PlayerObj : public Actor
{
public:
    PlayerObj(class Game *game);
    void UpdateActor(float deltaTime) override;
    void ProcessInput(const uint8_t *state, bool mouseDown);

private:
    float mPosY;
};