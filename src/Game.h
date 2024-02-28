#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include "Math.h"
#include "./Actors/Actor.h"
#include "./Scenes/Scene.h"
#include "./Actors/GuardWall.h"
#include "./Actors/WallHpBar.h"
#include "./Actors/Player.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Game
{
public:
    Game();
    // ゲームを初期化する
    bool Initialize();
    // ゲームオーバーまでゲームループを実行する
    void RunLoop();
    // ゲームをシャットダウンする
    void Shutdown();

    // アクターを追加する
    void AddActor(class Actor *actor);
    // アクターを削除する
    void RemoveActor(class Actor *actor);

    void AddSprite(class SpriteComponent *sprite);
    void RemoveSprite(class SpriteComponent *sprite);

    SDL_Texture *GetTexture(const std::string &fileName);
    std::string GetAssetsPath() const { return AssetsPath; }
    void AddEnemy(class Enemy *enemy);
    void RemoveEnemy(class Enemy *enemy);

private:
    void ProcessInput();
    // void UpdateGame();
    void StartScene();
    void UpdateScene();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    // C++の標準ライブラリの一部で、キーと値のペアを格納し、キーに基づいて迅速に値を検索することができるコンテナ
    std::unordered_map<std::string, SDL_Texture *> mTextures;
    //
    Uint32 mTicksCount;
    // SDLが作るウィンドウ
    SDL_Window *mWindow;
    // レンダラー
    SDL_Renderer *mRenderer;
    // ゲームの続行を指示する
    bool mIsRunning;
    // ゲーム中の全てのアクター
    std::vector<class Actor *> mActors;
    // 待ち状態のアクター
    std::vector<class Actor *> mPendingActors;

    std::vector<class SpriteComponent *> mSprites;
    // アクターを更新中の時true
    bool mUpdatingActors;

    // ゲームクリアかのフラグ
    bool mIsClear;
    // 現在のシーン
    Scene *mScene;
    // 次のシーン
    Scene *mNextScene;
    class Player *mShip;                 // プレイヤーの船
    class GuardWall *mGuardWall;         // プレイヤーを守る壁
    std::vector<class Enemy *> mEnemies; // エネミー
    class WallHpBar *mWallHpBar;
    class PlayerObj *mPlayer;

    // 画像パス
    const std::string AssetsPath = "./Assets/";

public:
    Scene *GetNextScene() const { return mNextScene; }
    void SetNextScene(class Scene *scene)
    {
        mNextScene = scene;
    }
    Scene *GetScene() const { return mScene; }
    void SetScene(class Scene *scene) { mScene = scene; }
    bool GetIsClear() { return mIsClear; }
    void SetIsClear(bool clear) { mIsClear = clear; }
    std::vector<class Enemy *> GetEnemies() { return mEnemies; }
    void SetPlayer(Player *tmpPlayer) { mShip = tmpPlayer; }
    void SetWall(GuardWall *tmpWall) { mGuardWall = tmpWall; }
    void SetWallHp(WallHpBar *tmpWallHpBar) { mWallHpBar = tmpWallHpBar; }
    Player *GetPlayer() { return mShip; }
    GuardWall *GetWall() { return mGuardWall; }
    WallHpBar *GetWallHpBar() { return mWallHpBar; }
    PlayerObj *GetPlayerObj() { return mPlayer; }
    void SetPlayerObj(PlayerObj *tmpPlayer) { mPlayer = tmpPlayer; }
};