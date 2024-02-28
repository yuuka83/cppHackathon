#pragma once
#include "SpriteComponent.h"
class BarSpriteComponent : public SpriteComponent
{
public:
    BarSpriteComponent(class Actor *owner, int drawOrder);
    ~BarSpriteComponent();
    void SetRatio(int current, int max);
    void Draw(SDL_Renderer *renderer) override;

private:
    float firstPosX;
    float firstPosY;
    float mRatio;
};