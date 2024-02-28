#pragma once
#include "PlayerObj.h"
#include "../Game.h"

PlayerObj::PlayerObj(Game *game)
    : Actor(game), mPosY(SCREEN_HEIGHT / 2)
{
    SetScale(0.2f);
    SpriteComponent *sc = new SpriteComponent(this, 20);
    SDL_Texture *tex = game->GetTexture(GetGame()->GetAssetsPath() + "player.png");
    SetPosition(Vector2(50, SCREEN_HEIGHT / 2));
    sc->SetTexture(tex);
}
void PlayerObj::UpdateActor(float deltaTime)
{

    Actor::UpdateActor(deltaTime);
    Vector2 pos = GetPosition();
    if (mPosY > 110 && mPosY < SCREEN_HEIGHT - 50)
    {
        pos.y = mPosY;
    }
    SetPosition(pos);
}
void PlayerObj::ProcessInput(const uint8_t *state, bool mouseDown)
{
    SDL_Point mouse_position;
    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);

    mPosY = mouse_position.y;
}