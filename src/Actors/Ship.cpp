#include "Ship.h"
#include "../Components/AnimSpriteComponent.h"
#include "../Game.h"
#include <iostream>

Ship::Ship(Game *game)
    : Actor(game), mRightSpeed(0.0f), mDownSpeed(0.0f)
{
    AnimSpriteComponent *asc = new AnimSpriteComponent(this);
    std::vector<SDL_Texture *> anims = {
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship01.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship02.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship03.png"),
        game->GetTexture(GetGame()->GetAssetsPath() + "Ship04.png"),
    };
    asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;

    if (pos.x < 25.0f)
    {
        pos.x = 25.0f;
    }
    else if (pos.x > 500.0f)
    {
        pos.x = 500.0f;
    }
    if (pos.y < 25.0f)
    {
        pos.y = 25.0f;
    }
    else if (pos.y > 743.0f)
    {
        pos.y = 743.0f;
    }
    SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t *state)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;
    if (state[SDL_SCANCODE_D])
    {
        mRightSpeed += 250.0f;
    }
    if (state[SDL_SCANCODE_A])
    {
        mRightSpeed -= 250.0f;
    }
    if (state[SDL_SCANCODE_S])
    {
        mDownSpeed += 300.0f;
    }
    if (state[SDL_SCANCODE_W])
    {
        mDownSpeed -= 300.0f;
    }
}