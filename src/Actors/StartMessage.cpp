#include "StartMessage.h"
#include "../Game.h"

StartMessage::StartMessage(Game *game)
    : Actor(game)
{
    SpriteComponent *sc = new SpriteComponent(this, 200);
    SDL_Texture *tex = game->GetTexture(GetGame()->GetAssetsPath() + "msg_start.png");
    SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    sc->SetTexture(tex);
}

void StartMessage::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}