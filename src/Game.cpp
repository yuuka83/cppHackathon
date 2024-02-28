#pragma once
#include "Game.h"
#include <iostream>
#include "SDL_image.h"
#include "./Components/SpriteComponent.h"
#include "./Actors/Player.h"
#include "./Actors/GuardWall.h"
#include "./Actors/Enemy.h"
#include "./Scenes/GameScene.h"
#include "./Scenes/ReadyScene.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
    : mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true)
{
}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("SDLを初期化できません:%s", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow(
        "2DGame",      // ウィンドウのタイトル
        100,           // ウィンドウの左上隅のx座標
        100,           // ウィンドウ左上すみのy座標
        SCREEN_WIDTH,  // ウィンドウの幅
        SCREEN_HEIGHT, // ウィンドウの高さ
        0              // フラグ
    );

    if (!mWindow)
    {
        SDL_Log("ウィンドウの作成に失敗しました:%s", SDL_GetError());
        return false;
    }
    // レンダラーを初期化
    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!mRenderer)
    {
        SDL_Log("レンダラーの初期化に失敗しました:%s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("SDL_imageの初期化に失敗しました: %s", SDL_GetError());
        return false;
    }

    LoadData();
    mTicksCount = SDL_GetTicks();
    return true;
}

void Game::RunLoop()
{
    mScene = new ReadyScene(this);
    mNextScene = mScene;
    StartScene();
    while (mIsRunning)
    {
        UpdateScene();
        // シーン開始処理
        // シーン開始処理
        if (mScene->GetSceneName().compare(mNextScene->GetSceneName()) != 0)
        {
            delete mScene;
            mScene = mNextScene;
            StartScene();
        }
    }
}

SDL_Texture *Game::GetTexture(const std::string &fileName)
{
    SDL_Texture *tex = nullptr;
    // fileNameキーに対応するエントリを検索
    // キーがマップ内に存在する場合はそのキーと値のペアを指すイテレータを返す
    auto iter = mTextures.find(fileName);
    // 検索が成功した場合
    if (iter != mTextures.end())
    {
        // キーと値のペアの「値」部分にアクセスしてtexに見つけたテクスチャを代入
        tex = iter->second;
    }
    // なかったら画像を新しく読み込み
    else
    {
        // ピクセルデータや画像のフォーマットなど、画像のビットマップ表現を保持するSDLの基本的な構造体
        SDL_Surface *surf = IMG_Load(fileName.c_str()); // const char*型（cスタイルの文字列）
        if (!surf)
        {
            SDL_Log("サーフェイスのファイルがロードできません%s", fileName.c_str());
            return nullptr;
        }
        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        if (!tex)
        {
            SDL_Log("サーフェイスからテクスチャに変換できません%s", fileName.c_str());
            return nullptr;
        }
        // コンテナ内に新しい要素を直接構築
        mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput()
{
    bool mouseDown = false;
    // SDLイベント
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: // ウィンドウが閉じられた時
            mIsRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseDown = true;
            break;
        }
    }
    // キー入力イベント
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
    // マウスイベント
    SDL_Point window_size = {SCREEN_WIDTH, SCREEN_HEIGHT};
    // SDL_Point mouse_position = {0, 0};
    mScene->ProcessInput(state, mouseDown);
    // mShip->ProcessInput(state, mouseDown);
}

void Game::StartScene()
{
    mScene->Start();
}
void Game::UpdateScene()
{
    ProcessInput();
    // 時間の更新
    // フレーム制限 フレーム間に必ず16ms経過するようにする
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    // 前のフレームとの時刻の差を秒に変換した値
    // SDL_GetTicksは初期化から経過したミリ秒数
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    // デルタタイムを最大値で制限する
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    // 時刻を更新
    mTicksCount = SDL_GetTicks();

    // 全てのアクターを更新
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    // 待ちアクターをアクターに追加
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor *> deadActors;
    // 死んだアクターをdeadActorsに追加
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }

    // 死んだアクターを削除
    for (auto actor : deadActors)
    {
        delete actor;
    }
    // シーンの更新処理
    mScene->Update(deltaTime);

    GenerateOutput();
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }
    // フロントバッファとバックバッファを交換
    SDL_RenderPresent(mRenderer);
}

// データをロードする
void Game::LoadData()
{
    auto *bgBack = new Actor(this);
    bgBack->SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    auto *bgBackSprite = new SpriteComponent(bgBack, 10);
    bgBackSprite->SetTexture(GetTexture(GetAssetsPath() + "back.png"));
    /*
    // 船を作る
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(100.0f, 384.0f));
    mShip->SetScale(1.5f);

    // 壁を作る
    mGuardWall = new GuardWall(this);

    // 体力ゲージを作る
    mWallHpBar = new WallHpBar(this);
    */
}

void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}

void Game::AddActor(Actor *actor)
{
    // アクターの更新中なら待ちに追加
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        // 更新中じゃなければアクティブアクターに追加
        mActors.emplace_back(actor);
    }
}
void Game::RemoveActor(Actor *actor)
{
    // 待ちアクターにいるか探す
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    // iterが待ちアクターの最後の次の位置じゃなければ（アクターが見つかったら）
    if (iter != mPendingActors.end())
    {
        // 最後の要素と交換
        std::iter_swap(iter, mPendingActors.end() - 1);
        // 末尾の要素を削除
        mPendingActors.pop_back();
    }

    // アクターにいるか探す
    iter = std::find(mActors.begin(), mActors.end(), actor);
    // アクターが見つかったら
    if (iter != mActors.end())
    {
        // 末尾に移動
        std::iter_swap(iter, mActors.end() - 1);
        // 末尾を削除
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent *sprite)
{
    int myDrowOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (myDrowOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent *sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Game::AddEnemy(Enemy *enemy)
{
    mEnemies.emplace_back(enemy);
}
void Game::RemoveEnemy(Enemy *enemy)
{
    auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
    if (iter != mEnemies.end())
    {
        mEnemies.erase(iter);
    }
}