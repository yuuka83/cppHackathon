#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

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

private:
    void ProcessInput();
    void UpdateGame();
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

    class Ship *mShip; // プレイヤーの船

    // 画像パス
    const std::string AssetsPath = "./Assets/";
};