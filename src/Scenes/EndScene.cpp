#pragma once
#include "EndScene.h"
#include "GameScene.h"
#include "ReadyScene.h"
#include "../Game.h"
#include "../Actors/Enemy.h"
#include "../Actors/PlayerObj.h"
#include "../Actors/Player.h"
EndScene::EndScene(Game *game)
    : Scene(game)
{
}
EndScene::~EndScene() {}
void EndScene::Start()
{
    // 開始メッセージの作成
    mEndMessage = new EndMessage(mGame);
}
void EndScene::Update(float deltaTime) {}
void EndScene::ProcessInput(const uint8_t *state, bool mouseDown)
{
    // std::cout << "a" << std::endl;
    // スペースかエンター押下でゲームシーンに遷移
    if (state[SDL_SCANCODE_R])
    {
        mGame->SetNextScene(new ReadyScene(mGame));
        mEndMessage->SetState(Actor::EDead);

        // プレイヤーと敵を削除
        Player *player = mGame->GetPlayer();
        player->SetState(Actor::EDead);

        PlayerObj *playerObj = mGame->GetPlayerObj();
        playerObj->SetState(Actor::EDead);

        for (auto enemy : mGame->GetEnemies())
        {
            enemy->SetState(Actor::EDead);
        }

        WallHpBar *WallHpBar = mGame->GetWallHpBar();
        WallHpBar->SetState(Actor::EDead);
        GuardWall *wall = mGame->GetWall();
        wall->SetState(Actor::EDead);
    }
}
std::string const EndScene::GetSceneName()
{
    return "End";
}