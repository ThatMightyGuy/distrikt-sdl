#include <stdio.h>

#include <engine/engine.h>
#include <engine/scene.h>

#include "scene/menu/scene.h"

int main() {
    engine_init();

    // Default scene would be scene/game
    scene_set(menu_scene);

    engine_handoff();

    engine_destroy();

    return 0;
}