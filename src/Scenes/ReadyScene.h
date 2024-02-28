#pragma once
#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/StartMessage.h"
class ReadyScene : public Scene
{
public:
    ReadyScene(Game *game);
    ~ReadyScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const uint8_t *state, bool mouseDown) override;
    std::string const GetSceneName() override;

private:
    StartMessage *mStartMessage;
};