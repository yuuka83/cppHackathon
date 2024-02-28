#include "Actor.h"
#include "../Components/ColliderComponent.h"
#pragma once
#include "../Components/AnimSpriteComponent.h"

class Enemy : public Actor
{
public:
    enum EnemyState
    {
        Walk,
        Idle,
        Attack
    };
    Enemy(Game *game);
    ~Enemy();
    void UpdateActor(float deltaTime) override;
    void Damage(int damage);

private:
    ColliderComponent *mColliderComp;
    std::vector<Vector2 *> mRnadPos; // 敵が出現する座標
    int mEnemySpeed;                 // 敵の速さ
    int mEnemyMaxHp;
    int mEnemyHp;
    EnemyState mEnemyState;
    bool mCollidingWallOnce;
    float mAttackTimer;
    float mAttackTime;

public: // ゲッター・セッター
    ColliderComponent *GetColliderComp() const { return mColliderComp; }
    int GetEnemyMaxHp() { return mEnemyMaxHp; }
    int GetEnemyHp() { return mEnemyHp; }
};