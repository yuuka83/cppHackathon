#include "../Components/SpriteComponent.h"
#include "../Actors/Actor.h"

class StartMessage : public Actor
{
public:
    StartMessage(class Game *game);
    void UpdateActor(float deltaTime) override;
};