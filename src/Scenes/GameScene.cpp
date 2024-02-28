#pragma once
#include "GameScene.h"
#include "../Game.h"
#include "../Actors/Enemy.h"
#include "../Actors/Player.h"
#include "../Actors/GuardWall.h"
#include "../Actors/Enemy.h"
#include "../Actors/Player.h"
#include "../Actors/PlayerObj.h"
#include "../Scenes/GameScene.h"
#include "../Scenes/EndScene.h"
#include <iostream>
GameScene::GameScene(Game *game)
    : Scene(game), mEnemyInstantiateTime(3), mGameEndTime(30)
{
    // プレイヤーレティクルとプレイヤーの作成
    Player *ship = new Player(mGame);
    ship->SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    mGame->SetPlayer(ship);
    // 壁の作成
    GuardWall *guardWall = new GuardWall(mGame);
    mGame->SetWall(guardWall);

    // 体力ゲージを作る
    WallHpBar *wallHpBar = new WallHpBar(mGame);
    mGame->SetWallHp(wallHpBar);
    mGameTimer = 0;
    mEnemyInstantiateTimer = 0;

    // プレイヤーの作成
    PlayerObj *player = new PlayerObj(mGame);
    mGame->SetPlayerObj(player);
}
GameScene::~GameScene(){};
void GameScene::Start()
{
}
void GameScene::Update(float deltaTime)
{
    mGameTimer += deltaTime;
    // 一定時間ごとに敵を生成
    mEnemyInstantiateTimer += deltaTime;
    if (mEnemyInstantiateTimer > mEnemyInstantiateTime)
    {
        mEnemyInstantiateTimer = 0;
        Enemy *enemy = new Enemy(mGame);
        int num = std::rand() % 5 + 1; // 1~5秒の間で生成
        mEnemyInstantiateTime = num;
    }
    // ゲーム終了
    if (mGameTimer > mGameEndTime)
    {
        // 終了シーンへ
        mGame->SetIsClear(true);
        mGame->SetNextScene(new EndScene(mGame));
    }
}
void GameScene::ProcessInput(const uint8_t *state, bool mouseDown)
{
    mGame->GetPlayer()->ProcessInput(state, mouseDown);
    mGame->GetPlayerObj()->ProcessInput(state, mouseDown);
}
std::string const GameScene::GetSceneName() { return "Game"; }