#include "Game.h"
#include "EntityPlayer.h"
#include "EntityEnemy.h"

Game::Game() :
    numDead(0),
    levelComplete(false)
{
    // Load textures
    texPlayer = CORE_LoadPNG("data/survivor.png",  false);
    texFloor  = CORE_LoadPNG("data/tilefloor.png", false);
    texEnemy  = CORE_LoadPNG("data/rifleman.png",  false);
    texBlood  = CORE_LoadPNG("data/blood.png",     false);
    texSlash  = CORE_LoadPNG("data/slash.png",     false);
    // Entities
    Entity *player = new EntityPlayer(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 20), 6.f, texPlayer, 25.f, 90.f, true, 50.f, texSlash);
    entities.push_back(player);
    LoadLevel();
}

Game::~Game() {
    // Textures
    CORE_UnloadPNG(texPlayer);
    CORE_UnloadPNG(texFloor);
    CORE_UnloadPNG(texEnemy);
    CORE_UnloadPNG(texBlood);
    CORE_UnloadPNG(texSlash);
    // Pointers
    for (auto entity : entities) delete entity;
    entities.clear();
}

void Game::Render() {
    // Render background
    for (int i = 0; i <= SCR_WIDTH / 128; i++)
        for (int j = 0; j <= SCR_HEIGHT / 128; j++)
            CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f),
                vmake(128.f, 128.f), texFloor);
    //Render entities
    for (auto entity : entities)
        entity->Render();
}

void Game::Run() {
    for (auto entity : entities)
        entity->Run();
}

bool Game::IsLevelComplete() { return levelComplete; }

void Game::LoadLevel() {
    Entity *enemy1 = new EntityEnemy(vmake(30.f, 100.f), 8.f, texEnemy, 25.f, 0.f, true, texBlood);
    Entity *enemy2 = new EntityEnemy(vmake(100.f, 400.f), 8.f, texEnemy, 25.f, 0.f, true, texBlood);
    Entity *enemy3 = new EntityEnemy(vmake(450.f, 350.f), 8.f, texEnemy, 25.f, 0.f, true, texBlood);
    entities.push_back(enemy1);
    entities.push_back(enemy2);
    entities.push_back(enemy3);
}

float Game::Distance(const vec2 &pos1, const vec2 &pos2) {
    vec2 dir = vmake(pos2.x - pos1.x, pos2.y - pos1.y);
    return sqrtf(dir.x * dir.x + dir.y * dir.y);
}

void Game::CheckKill(const vec2& playerPos, const float playerRange) {
    for (auto entity : entities) {
        if (entity->GetAlive() && Distance(playerPos, entity->GetPos()) < playerRange) {
            entity->SetAlive(false);
            ++numDead;
        }
    }
    // All dead: level cleared
    if (numDead == entities.size()) levelComplete = true;
}