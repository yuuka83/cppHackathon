#include "GuardWall.h"

GuardWall::GuardWall(Game *game)
    : Actor(game), mWallHp(100)
{
}
void GuardWall::UpdateActor(float deltaTime)
{
    // 敵が当たっていたら
    // 体力が減る
}