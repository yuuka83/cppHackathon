cmake_minimum_required(VERSION 3.20)
project(2DShootingGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(2DShootingGame src/main.cpp src/Game.cpp src/Game.h src/Math.h src/Math.cpp src/Actors/Actor.h src/Actors/Actor.cpp src/Actors/Enemy.h src/Actors/Enemy.cpp src/Actors/GuardWall.h src/Actors/GuardWall.cpp src/Actors/WallHpBar.h src/Actors/WallHpBar.cpp src/Actors/StartMessage.h src/Actors/StartMessage.cpp src/Actors/EndMessage.h src/Actors/EndMessage.cpp src/Actors/Player.h src/Actors/Player.cpp src/Actors/PlayerObj.h src/Actors/PlayerObj.cpp src/Components/Component.h src/Components/Component.cpp src/Components/SpriteComponent.h src/Components/SpriteComponent.cpp src/Components/AnimSpriteComponent.h src/Components/AnimSpriteCompoment.cpp src/Components/BarSpriteComponent.h src/Components/BarSpriteComponent.cpp src/Components/ColliderComponent.h src/Components/ColliderComponent.cpp src/Scenes/Scene.h src/Scenes/Scene.cpp src/Scenes/GameScene.h src/Scenes/GameScene.cpp src/Scenes/ReadyScene.h src/Scenes/ReadyScene.cpp src/Scenes/EndScene.h src/Scenes/EndScene.cpp)

# SDL2のパスを設定
# 自身の環境に合わせて書き換えるべし
set(SDL2_LIB_PATH "/opt/homebrew/Cellar/sdl2/2.30.0/lib/libSDL2-2.0.0.dylib")
set(SDL2_IMAGE_LIB_PATH "/opt/homebrew/Cellar/sdl2_image/2.8.2/lib/libSDL2_image-2.0.0.dylib")
include_directories("/opt/homebrew/Cellar/sdl2/2.30.0/include/SDL2")
include_directories("/opt/homebrew/Cellar/sdl2_image/2.8.2/include/SDL2")

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_PATH} ${SDL2_IMAGE_LIB_PATH})
