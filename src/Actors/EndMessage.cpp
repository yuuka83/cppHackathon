#include "EndMessage.h"
#include "../Game.h"

EndMessage::EndMessage(Game *game)
    : Actor(game)
{
    SDL_Texture *tex;
    if (GetGame()->GetIsClear() != true)
    {
        tex = game->GetTexture(GetGame()->GetAssetsPath() + "msg_over.png");
    }
    else
    {
        tex = game->GetTexture(GetGame()->GetAssetsPath() + "msg_clear.png");
    }
    SpriteComponent *sc = new SpriteComponent(this, 200);

    SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    sc->SetTexture(tex);
}

void EndMessage::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}