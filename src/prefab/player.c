#include "player.h"

void player_init(player_t *player)
{
    player->object = object_init();

    spriterender_init(&player->sprite);
    player->sprite.texture  = texture_load("assets/test.jpg");
    add_component(&player->object, &player->sprite);

    debugrender_init(&player->debug);
    player->debug.enabled = false;
    add_component(&player->object, &player->debug);
}

void player_destroy(player_t *player)
{
    object_destroy(&player->object);
}