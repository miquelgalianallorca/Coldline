#include "Game.h"
#include "EntityPlayer.h"
#include "EntityEnemy.h"
#include "EntityBullet.h"

Game::Game() :
    numDead(0),
    levelComplete(false),
    playerSlashing(false)
{
    // Entities
    player = new EntityPlayer(vmake(SCR_WIDTH / 2, SCR_HEIGHT / 20), 6.f, 25.f, 90.f, true, 50.f);
    entities.push_back(player);
    LoadLevel();
}

Game::~Game() {
    for (auto entity : entities) delete entity;
    player = nullptr;
    entities.clear();
    enemies.clear();
    bullets.clear();
}

void Game::Render() {
    // Render background
    for (int i = 0; i <= SCR_WIDTH / 128; i++)
        for (int j = 0; j <= SCR_HEIGHT / 128; j++)
            graphicsEngine.Draw(GraphicsEngine::Sprite::FLOOR, vmake(i * 128.f + 64.f, j * 128.f + 64.f),
                vmake(128.f, 128.f), 0.f);
    
    //================================================================= Entities
    // Render enemies
    for (auto enemy : enemies) {
        if (enemy->GetAlive())
            graphicsEngine.Draw(GraphicsEngine::Sprite::ENEMY, enemy->GetPos(),
                vmake(enemy->GetRadius() * 2, enemy->GetRadius() * 2), enemy->GetAngle());
        else
            graphicsEngine.Draw(GraphicsEngine::Sprite::BLOOD, enemy->GetPos(),
                vmake(enemy->GetRadius() * 2, enemy->GetRadius() * 2), enemy->GetAngle());
    }

    // Render player
    graphicsEngine.Draw(GraphicsEngine::Sprite::PLAYER, player->GetPos(),
        vmake(player->GetRadius() * 2, player->GetRadius() * 2), player->GetAngle());
    if (playerSlashing)
        graphicsEngine.Draw(GraphicsEngine::Sprite::SLASH, player->GetPos(),
            vmake(player->GetRadius() * 2, player->GetRadius() * 2), player->GetAngle());
    
    // Render bullets
    for (auto bullet : bullets) {
        graphicsEngine.Draw(GraphicsEngine::Sprite::BULLET, bullet->GetPos(),
            vmake(bullet->GetRadius() * 2, bullet->GetRadius() * 2), bullet->GetAngle());
    }
    //===========================================================================
}

void Game::Run() {
    for (auto entity : entities) {
        entity->Run();
    }
    // Can't add to iterator while iterating, so bullets are added later
    for (auto bullet : bullets) entities.push_back(bullet);
}

bool Game::IsLevelComplete() { return levelComplete; }

void Game::LoadLevel() {
    // TO DO: Read from JSON
    Entity *enemy1 = new EntityEnemy(vmake(30.f,  100.f), 8.f, 25.f, 0.f, true, 20);
    Entity *enemy2 = new EntityEnemy(vmake(100.f, 400.f), 8.f, 25.f, 90.f, true, 20);
    Entity *enemy3 = new EntityEnemy(vmake(450.f, 350.f), 8.f, 25.f, -90.f, true, 20);
    entities.push_back(enemy1);
    entities.push_back(enemy2);
    entities.push_back(enemy3);
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
}

float Game::Distance(const vec2 &pos1, const vec2 &pos2) {
    vec2 dir = vmake(pos2.x - pos1.x, pos2.y - pos1.y);
    return sqrtf(dir.x * dir.x + dir.y * dir.y);
}

void Game::CheckKill(const vec2& playerPos, const float playerRange) {
    for (auto enemy : enemies) {
        if (enemy->GetAlive() && Distance(playerPos, enemy->GetPos()) < playerRange) {
            enemy->SetAlive(false);
            ++numDead;
        }
    }
    // All dead: level cleared
    if (numDead == enemies.size()) levelComplete = true;
}

void Game::ProcessInput(Action action) {
    // Player input
    vec2  newPos   = player->GetPos();
    float newAngle = player->GetAngle();
    float vel      = player->GetVel();
    switch (action) {
        case Action::MOVE_U:
            newPos = vadd(newPos, vmake(0, vel));
            newAngle = 90.f;
            break;
        case Action::MOVE_D:
            newPos = vadd(newPos, vmake(0, -vel));
            newAngle = -90.f;
            break;
        case Action::MOVE_L:
            newPos = vadd(newPos, vmake(-vel, 0));
            newAngle = 179.f;
            break;
        case Action::MOVE_R:
            newPos = vadd(newPos, vmake(vel, 0));
            newAngle = 0.f;
            break;
        case Action::SLASH:
            player->Attack();
    }
    player->Move(newPos, newAngle);
}

void Game::SetSlashing(bool value) { playerSlashing = value; }

void Game::AddBullet(vec2 pos, float angle) {
    Entity *bullet = new EntityBullet(pos, 20.f, 15.f, angle, true);
    bullets.push_back(bullet);
}