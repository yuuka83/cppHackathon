#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
    GameScene(class Game *game);
    ~GameScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const uint8_t *state, bool mouseDown) override;
    std::string const GetSceneName() override;

private:
    float mEnemyInstantiateTimer;
    float mEnemyInstantiateTime;
    float mGameTimer;
    float mGameEndTime;
};