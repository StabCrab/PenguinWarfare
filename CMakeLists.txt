cmake_minimum_required(VERSION 3.17)
project(PenguinWarfare)

set(CMAKE_CXX_STANDARD 20)

add_executable(PenguinWarfare main.cpp
        Menu.h Menu.cpp
        GameWorld.h GameWorld.cpp
        Terrain.h Terrain.cpp
        Player.h Player.cpp
        Entity.h Entity.cpp
        Unit.h Unit.cpp
        Weapon.h Weapon.cpp
        InputHandler.h InputHandler.cpp
        Animation.h Animation.cpp
        Projectile.h Projectile.cpp
        Crosshair.h Crosshair.cpp)

set(SFML_ROOT "D:/Libraries/SFML")

set(CMAKE_MODULE_PATH "D:/Libraries/SFML/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics network audio window system )

include_directories(D:/Libraries/SFML/include/SFML)
target_link_libraries(PenguinWarfare D:/Libraries/SFML/lib sfml-graphics sfml-network sfml-audio sfml-window sfml-system)