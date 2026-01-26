#include "scene.h"

const float sizeMul = 40.0;

const float gravity = -9.8 * sizeMul;
const float maxSpeed = 10 * sizeMul;
const float maxCrouchSpeed = 2 * sizeMul;
const float accel = 20 * sizeMul;
const float jumpForce = 7 * sizeMul;
const float dashStrength = 2;

const float walkDrag = 2;
const float crouchDrag = 2;
const float airDrag = 1.05;

const float cameraSpeed = 200;

object_t player;

void game_init()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Game Init!");
    engine_set_clear_colorB(20, 20, 20, 255);
    player = object_init();
    player.position = (SDL_FPoint) { 150, 250 };
    player.scale    = (SDL_FPoint) { 10, 45 };
    player.origin   = (SDL_FPoint) { 5, -45 };

}

object_t grid;

#define GRID_SIZE 50
const SDL_FPoint gridPoints[GRID_SIZE * GRID_SIZE];
void draw_grid()
{
    const float spacing = 50;
    for(int x = -GRID_SIZE / 2; x < GRID_SIZE / 2 - 1; x++)
        for(int y = -GRID_SIZE / 2; y < GRID_SIZE / 2 - 1; y++)
        {
            SDL_FPoint p = { x * spacing, y * spacing };
            p = world_to_screen(p);
            SDL_RenderPoint(Renderer, p.x, p.y);
        }
}

// SDL_FPoint player_pos = { 150, 250 };
SDL_FPoint player_vel;

bool isGrounded = false;
bool jumpLock = false;
bool dashEnded = false;

void game_update(float deltaTime)
{
    if(input_key(SDL_SCANCODE_ESCAPE))
        engine_exit();

    SDL_SetRenderDrawColor(Renderer, SDL_fmodf(scene_time(), 1) * 55 + 200, 0, 0, 255);
    SDL_RenderDebugTextFormat(Renderer, 16, 16, "T: %.3f dT: %.4f", scene_time(), deltaTime);
    SDL_RenderDebugTextFormat(Renderer, 16, 32, "FT: %.2f (%d) fps", engine_get_frametime(), (int)engine_get_framerate());
    SDL_RenderDebugTextFormat(Renderer, 16, 48, "grounded: %d dash: %d", isGrounded, !jumpLock);
    SDL_RenderDebugTextFormat(Renderer, 16, 64, "vel_x: %03.2f vel_y: %03.2f", player_vel.x, player_vel.y);

    float hoz = input_get("input_hoz") / 32767.0;
    float vert = input_get("input_vert") / 32767.0;
    bool isCrouched = vert < -0.5;

    if(isCrouched)
    {
        player.scale  = (SDL_FPoint) { 10, 25 };
        player.origin = (SDL_FPoint) { 5, -25 };
    }
    else
    {
        player.scale  = (SDL_FPoint) { 10, 45 };
        player.origin = (SDL_FPoint) { 5, -45 };
    }

    if(vert > 0.5)
    {
        if(isGrounded)
        {
            player_vel.y = jumpForce;
            isGrounded = false;
        }
        else if(!jumpLock && player_vel.y < 0)
        {
            player_vel.y = jumpForce;
            player_vel.x *= dashStrength;
            jumpLock = true;
            dashEnded = false;
        }
    }
    if(!dashEnded && !isGrounded && jumpLock && player_vel.y > 0)
    {
        dashEnded = true;
        player_vel.x /= dashStrength * 2;
    }
    if(SDL_fabsf(player_vel.x) < (isCrouched ? maxCrouchSpeed : maxSpeed))
    {
        player_vel.x += hoz * accel * deltaTime;
    }

    float choz = input_get("input_cam_hoz") / 32767.0;
    float cvert = input_get("input_cam_vert") / 32767.0;

    float t = 2 * deltaTime;

    Camera->position.x = Camera->position.x * (1 - t) + (player.position.x + choz * cameraSpeed) * t;
    Camera->position.y = Camera->position.y * (1 - t) + (player.position.y + player.scale.y * 1.5 + cvert * cameraSpeed) * t;

    int rw, rh;
    SDL_GetCurrentRenderOutputSize(Renderer, &rw, &rh);
    float sw, sh;
    SDL_GetRenderScale(Renderer, &sw, &sh);
    float w = rw / sw;
    float h = rh / sh;

    float drag;
    if(player.position.y <= 0)
    {
        player.position.y = 0;
        isGrounded = true;
        jumpLock = false;

        if(isCrouched)
            drag = crouchDrag;
        else
            drag = walkDrag;
    }
    else
    {
        isGrounded = false;
        player_vel.y += gravity * deltaTime;
        drag = airDrag;
    }

    player_vel.x -= player_vel.x * drag * deltaTime;
    player_vel.y -= player_vel.y * drag * deltaTime;

    player.position.x += player_vel.x * deltaTime;
    player.position.y += player_vel.y * deltaTime;


    SDL_FRect floor = { 0, h / 2 + Camera->position.y, w, h };
    //SDL_FRect player = { player.position.x - 5, player.position.y, 10, isCrouched ? -25 : -45 };

    SDL_SetRenderDrawColor(Renderer, 50, 50, 50, 255);
    draw_grid();
    
    SDL_SetRenderDrawColorFloat(Renderer, 0.09, 0.57, 0.32, 1);
    SDL_RenderFillRect(Renderer, &floor);
    // SDL_SetRenderDrawColorFloat(Renderer, 0.9, 0.9, 0.9, 1);
    // SDL_RenderFillRect(Renderer, &player);
    scene_drawdebug(player);
}

int game_destroy()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Game Destroy!");
    return 0;
}
