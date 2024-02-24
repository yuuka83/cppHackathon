cmake_minimum_required(VERSION 3.20)
project(2DShootingGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(2DShootingGame src/main.cpp src/Game.cpp src/Game.h src/Math.h src/Math.cpp src/Actors/Actor.h src/Actors/Actor.cpp src/Actors/Ship.h src/Actors/Ship.cpp src/Components/Component.h src/Components/Component.cpp src/Components/SpriteComponent.h src/Components/SpriteComponent.cpp src/Components/AnimSpriteComponent.h src/Components/AnimSpriteCompoment.cpp)

# SDL2のパスを設定
# 自身の環境に合わせて書き換えるべし
set(SDL2_LIB_PATH "/opt/homebrew/Cellar/sdl2/2.30.0/lib/libSDL2-2.0.0.dylib")
set(SDL2_IMAGE_LIB_PATH "/opt/homebrew/Cellar/sdl2_image/2.8.2/lib/libSDL2_image-2.0.0.dylib")
include_directories("/opt/homebrew/Cellar/sdl2/2.30.0/include/SDL2")
include_directories("/opt/homebrew/Cellar/sdl2_image/2.8.2/include/SDL2")

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_PATH} ${SDL2_IMAGE_LIB_PATH})
