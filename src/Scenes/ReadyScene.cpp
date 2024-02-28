#pragma once
#include "ReadyScene.h"
#include "GameScene.h"
#include "../Game.h"

ReadyScene::ReadyScene(Game *game)
    : Scene(game)
{
}
ReadyScene::~ReadyScene() {}
void ReadyScene::Start()
{
    mGame->SetIsClear(false);
    // 開始メッセージの作成
    mStartMessage = new StartMessage(mGame);
}
void ReadyScene::Update(float deltaTime) {}
void ReadyScene::ProcessInput(const uint8_t *state, bool mouseDown)
{
    // std::cout << "a" << std::endl;
    // スペースかエンター押下でゲームシーンに遷移
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
    {
        mGame->SetNextScene(new GameScene(mGame));
        mStartMessage->SetState(Actor::EDead);
    }
}
std::string const ReadyScene::GetSceneName()
{
    return "Start";
}