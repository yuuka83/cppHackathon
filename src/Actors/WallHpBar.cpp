#include "WallHpBar.h"
#include "../Game.h"

WallHpBar::WallHpBar(Game *game)
    : Actor(game)
{
    SDL_Texture *tex = game->GetTexture(GetGame()->GetAssetsPath() + "hp_in.png");
    SetScale(1.3f);
    SetPosition(Vector2(SCREEN_WIDTH / 2 - 180, 10));
    mBsc = new BarSpriteComponent(this, 102);
    mBsc->SetTexture(tex);
}

void WallHpBar::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}