#include "Game.h"

void LoadLevel(std::vector<Entity> &enemies, GLuint texEnemy) {
    Entity enemy1;
    enemy1.pos = vmake(30.f, 100.f);
    enemy1.vel = 8.f;
    enemy1.radius = 25.f;
    enemy1.gfx = texEnemy;
    enemy1.angle = 0.f;
    enemy1.alive = true;
    enemies.push_back(enemy1);
    Entity enemy2;
    enemy2.pos = vmake(100.f, 400.f);
    enemy2.vel = 8.f;
    enemy2.radius = 25.f;
    enemy2.gfx = texEnemy;
    enemy2.angle = 0.f;
    enemy2.alive = true;
    enemies.push_back(enemy2);
    Entity enemy3;
    enemy3.pos = vmake(450.f, 350.f);
    enemy3.vel = 8.f;
    enemy3.radius = 25.f;
    enemy3.gfx = texEnemy;
    enemy3.angle = -90.f;
    enemy3.alive = true;
    enemies.push_back(enemy3);
}

float Distance(const vec2 &pos1, const vec2 &pos2) {
    vec2 dir = vmake(pos2.x - pos1.x, pos2.y - pos1.y);
    float dist = sqrtf(dir.x * dir.x + dir.y * dir.y);

    /* char buffer[100];
    sprintf_s(buffer, "Dist: %f\n", dist);
    OutputDebugStringA(buffer);*/

    return dist;
}

Game::Game() {
    // Load textures
    texPlayer = CORE_LoadPNG("data/survivor.png",  false);
    texFloor  = CORE_LoadPNG("data/tilefloor.png", false);
    texEnemy  = CORE_LoadPNG("data/rifleman.png",  false);
    texBlood  = CORE_LoadPNG("data/blood.png",     false);
    texSlash  = CORE_LoadPNG("data/slash.png",     false);
    // Player
    playerRange = 50.f;
    slashTimer  = 0;
    player.pos = vmake(SCR_WIDTH / 2, SCR_HEIGHT / 20);
    player.vel = 6.f;
    player.radius = 25.f;
    player.gfx = texPlayer;
    player.angle = 90.f;
    // Enemies
    LoadLevel(enemies, texEnemy);
}

Game::~Game() {
    CORE_UnloadPNG(texPlayer);
    CORE_UnloadPNG(texFloor);
    CORE_UnloadPNG(texEnemy);
    CORE_UnloadPNG(texBlood);
    CORE_UnloadPNG(texSlash);
}

void Game::Render() {
    // Render background
    for (int i = 0; i <= SCR_WIDTH / 128; i++)
        for (int j = 0; j <= SCR_HEIGHT / 128; j++)
            CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f), vmake(128.f, 128.f), texFloor);

    //Render enemies
    for (auto enemy : enemies) {
        if (enemy.alive)
            CORE_RenderCenteredRotatedSprite(enemy.pos, vmake(enemy.radius * 2.f, enemy.radius * 2.f), enemy.angle, enemy.gfx);
        else
            CORE_RenderCenteredRotatedSprite(enemy.pos, vmake(enemy.radius * 2.f, enemy.radius * 2.f), enemy.angle, texBlood);
    }

    //Render player
    CORE_RenderCenteredRotatedSprite(player.pos, vmake(player.radius * 2.f, player.radius * 2.f), player.angle, player.gfx);

    //Render effects
    if (slashTimer > 0) {
        CORE_RenderCenteredRotatedSprite(player.pos, vmake(player.radius * 2.f, player.radius * 2.f), player.angle, texSlash);
    }
}

void Game::Run() {
    // Move
    vec2 newpos = player.pos;
    if (SYS_KeyPressed(SYS_KEY_UP)) { newpos = vadd(newpos, vmake(0, player.vel));  player.angle = 90.f; }
    if (SYS_KeyPressed(SYS_KEY_DOWN)) { newpos = vadd(newpos, vmake(0, -player.vel)); player.angle = -90.f; }
    if (SYS_KeyPressed(SYS_KEY_LEFT)) { newpos = vadd(newpos, vmake(-player.vel, 0)); player.angle = 179.f; }
    if (SYS_KeyPressed(SYS_KEY_RIGHT)) { newpos = vadd(newpos, vmake(player.vel, 0)); player.angle = 0.f; }
    player.pos = newpos;

    // Slash
    if (SYS_MouseButonPressed(SYS_MB_LEFT)) {
        slashTimer = 10;
        for (auto& enemy : enemies) {
            if (Distance(player.pos, enemy.pos) < playerRange)
                enemy.alive = false;
        }
    }
    if (slashTimer > 0) {
        --slashTimer;
    }
}