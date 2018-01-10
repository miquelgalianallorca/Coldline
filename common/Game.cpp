#include "Game.h"
#include "Entity.h"

void LoadLevel(std::vector<Entity*> &enemies, GLuint texEnemy) {
    Entity *enemy1 = new Entity(vmake(30.f, 100.f), 8.f, texEnemy, 25.f, 0.f, true);
    Entity *enemy2 = new Entity(vmake(100.f, 400.f), 8.f, texEnemy, 25.f, 0.f, true);
    Entity *enemy3 = new Entity(vmake(450.f, 350.f), 8.f, texEnemy, 25.f, 0.f, true);
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
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

Game::Game() :
    playerRange(50.f),
    slashTimer(0),
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
    player = new Entity(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 20), 6.f, texPlayer, 25.f, 90.f, true);
    LoadLevel(enemies, texEnemy);
}

Game::~Game() {
    // Textures
    CORE_UnloadPNG(texPlayer);
    CORE_UnloadPNG(texFloor);
    CORE_UnloadPNG(texEnemy);
    CORE_UnloadPNG(texBlood);
    CORE_UnloadPNG(texSlash);
    // Pointers
    delete player;
    for (auto enemy : enemies) delete enemy;
    enemies.clear();
}

void Game::Render() {
    // Render background
    for (int i = 0; i <= SCR_WIDTH / 128; i++)
        for (int j = 0; j <= SCR_HEIGHT / 128; j++)
            CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f),
                vmake(128.f, 128.f), texFloor);

    //Render enemies
    for (auto enemy : enemies) {
        if (enemy->GetAlive())
            CORE_RenderCenteredRotatedSprite(enemy->GetPos(), vmake(enemy->GetRadius() * 2.f,
                enemy->GetRadius() * 2.f), enemy->GetAngle(), enemy->GetGfx());
        else
            CORE_RenderCenteredRotatedSprite(enemy->GetPos(), vmake(enemy->GetRadius() * 2.f,
                enemy->GetRadius() * 2.f), enemy->GetAngle(), texBlood);
    }

    //Render player
    CORE_RenderCenteredRotatedSprite(player->GetPos(), vmake(player->GetRadius() * 2.f, player->GetRadius() * 2.f),
        player->GetAngle(), player->GetGfx());

    //Render effects
    if (slashTimer > 0) {
        CORE_RenderCenteredRotatedSprite(player->GetPos(), vmake(player->GetRadius() * 2.f, player->GetRadius() * 2.f),
            player->GetAngle(), texSlash);
    }
}

void Game::Run() {
    // Move
    vec2 newPos = player->GetPos();
    if (SYS_KeyPressed(SYS_KEY_UP))    { newPos = vadd(newPos, vmake(0, player->GetVel()));  player->SetAngle(90.f);  }
    if (SYS_KeyPressed(SYS_KEY_DOWN))  { newPos = vadd(newPos, vmake(0, -player->GetVel())); player->SetAngle(-90.f); }
    if (SYS_KeyPressed(SYS_KEY_LEFT))  { newPos = vadd(newPos, vmake(-player->GetVel(), 0)); player->SetAngle(179.f); }
    if (SYS_KeyPressed(SYS_KEY_RIGHT)) { newPos = vadd(newPos, vmake(player->GetVel(), 0));  player->SetAngle(0.f);   }
    player->SetPos(newPos);

    // Slash
    if (SYS_MouseButonPressed(SYS_MB_LEFT)) {
        slashTimer = 10;
        for (auto enemy : enemies) {
            if (enemy->GetAlive() && Distance(player->GetPos(), enemy->GetPos()) < playerRange) {
                enemy->SetAlive(false);
                ++numDead;
            }
        }
        // All dead: level cleared
        if (numDead == enemies.size()) levelComplete = true;
    }
    if (slashTimer > 0) --slashTimer;
}

bool Game::IsLevelComplete() { return levelComplete; }
