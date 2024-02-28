#pragma once
#include "Scene.h"
#include "../Game.h"

Scene::Scene(class Game *game)
    : mGame(game){

      };
Scene::~Scene()
{
}
void Scene::Start()
{
}
void Scene::Update(float deltaTime)
{
}
void Scene::ProcessInput(const uint8_t *state, bool mouseDown)
{
}
std::string const Scene::GetSceneName() { return ""; }