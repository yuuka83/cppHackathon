#pragma once
#include "SDL.h"
#include "string"

class Scene
{
public:
    Scene(class Game *game);
    virtual ~Scene();
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void ProcessInput(const uint8_t *state, bool mouseDown);
    virtual std::string const GetSceneName();

protected:
    class Game *mGame;
};
