#pragma once
#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/EndMessage.h"

class EndScene : public Scene
{
public:
    EndScene(Game *game);
    ~EndScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const uint8_t *state, bool mouseDown) override;
    std::string const GetSceneName() override;

private:
    EndMessage *mEndMessage;
};