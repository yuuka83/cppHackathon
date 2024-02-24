#pragma once
#include <vector>
#include "../Math.h"
class Actor
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };
    // コンストラクタとデストラクタ
    Actor(class Game *game);
    virtual ~Actor();
    // ゲームから呼び出される更新関数（オーバーライド不可）
    void Update(float deltaTime);
    // アクターが持つ全コンポーネントを更新（オーバーライド不可）
    void UpdateComponents(float deltaTime);
    // アクター独自の更新処理
    virtual void UpdateActor(float deltaTime);
    // ゲッター・セッター
    // 位置のアドレスを返す
    const Vector2 &GetPosition() { return mPosition; }
    // 位置を設定する
    void SetPosition(const Vector2 &pos) { mPosition = pos; }
    // スケールを返す
    float GetScale() const { return mScale; }
    // スケールをセットする
    void SetScale(float scale) { mScale = scale; }
    // 回転をゲットする
    float GetRotation() const { return mRotation; }
    // 回転をセットする
    void SetRotation(float rotation) { mRotation = rotation; }

    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    class Game *GetGame() { return mGame; }

    // コンポーネントの追加/削除
    void AddComponent(class Component *component);
    void RemoveComponent(class Component *component);

private:
    State mState; // アクターの状態
    // トランスフォーム
    Vector2 mPosition; // アクターの中心位置
    float mScale;      // アクターのスケール(1.0fが100%)
    float mRotation;
    std::vector<class Component *> mComponents;
    class Game *mGame;
};