#include "../Components/SpriteComponent.h"
#include "../Actors/Actor.h"

class EndMessage : public Actor
{
public:
    EndMessage(class Game *game);
    void UpdateActor(float deltaTime) override;
};