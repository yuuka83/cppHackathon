#include "CircleColliderComponent.h"
#include "../Actors/Actor.h"
#include <iostream>

// 中心位置を取得
// 関数の呼び出し側で変更されることを防ぐ
// const末尾：この関数がクラスのメンバ変数を変更しないことを示し
const Vector2 &CircleColliderComponent::GetCenterPosition() const
{
    return mOwner->GetPosition();
}
// スケールを考慮した半径を取得
const float CircleColliderComponent::GetRadius()
{
    return mOwner->GetScale() * mRadius;
}
// 衝突し始めを検知
bool CircleColliderComponent::OnCollisionEnter(ColliderComponent &a, ColliderComponent &b)
{

    // 初めて衝突を検知したら
    if (mCollisionEnter == false)
    {
        // 2点間の距離
        Vector2 diff = a.GetCenterPosition() - b.GetCenterPosition();
        // ベクトルの大きさを求める
        float diffMagnitude = Math::roundToDecimalPlace(diff.LengthSq(), 2);

        // 2点間の距離が二つの縁の半径の和の二乗と等しいなら
        float radSum = Math::roundToDecimalPlace(a.mRadius + b.mRadius, 2);
        radSum = radSum * radSum;
        if (diffMagnitude == radSum)
        {
            mCollisionEnter = true;
            std::cout << "衝突し始めた" << std::endl;
            return true;
        }
    }
    return false;
}
// 衝突している時を検知
bool CircleColliderComponent::OnCollisionStay(ColliderComponent &a, ColliderComponent &b)
{
    // 2点間の距離
    Vector2 diff = a.GetCenterPosition() - b.GetCenterPosition();
    // ベクトルの大きさを求める
    float diffMagnitude = diff.LengthSq();
    // 2点間の距離が二つの縁の半径の和の二乗と等しいなら
    float radSum = a.mRadius + b.mRadius;
    if (diffMagnitude < radSum * radSum)
    {
        std::cout << "衝突中" << std::endl;
        return true;
    }
    return false;
}

// 衝突し終わった時を検知
bool CircleColliderComponent::OnCollisionExit(ColliderComponent &a, ColliderComponent &b)
{
    // 初めて衝突を検知したら
    if (mCollisionEnter == true)
    {
        // 2点間の距離
        Vector2 diff = a.GetCenterPosition() - b.GetCenterPosition();
        // ベクトルの大きさを求める
        float diffMagnitude = Math::roundToDecimalPlace(diff.LengthSq(), 2);

        // 2点間の距離が二つの縁の半径の和の二乗と等しいなら
        float radSum = Math::roundToDecimalPlace(a.mRadius + b.mRadius, 2);
        radSum = radSum * radSum;
        if (diffMagnitude == radSum)
        {
            mCollisionEnter = false;
            std::cout << "衝突し終わった" << std::endl;
            return true;
        }
    }
    return false;
}