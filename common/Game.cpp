#include "Game.h"

#include "Component.h"
#include "ComponentBullet.h"
#include "ComponentCollider.h"
#include "ComponentEnemy.h"
#include "ComponentPlayer.h"
#include "ComponentRenderable.h"
#include "Entity.h"
#include "Message.h"

#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

Game::Game(Difficulty diff) :
    enemiesLeft(0),
    isPlayerDead(false)
{
    // Entities
    LoadPlayer();
    LoadFloor();
    LoadLevelJSON(diff);
}

Game::~Game() {
    for (auto entity : entities) delete entity;
    player = nullptr;
    entities.clear();
    //enemies.clear();
    //bullets.clear();
}

// LOADING ========================================================
void Game::LoadFloor() {
    Entity *floor = new Entity(this);
    GraphicsEngine::Drawable drawable;
    drawable.sprite   = GraphicsEngine::Sprite::FLOOR;
    drawable.pos      = vmake(0.f, 0.f);
    drawable.size     = vmake(128.f, 128.f);
    drawable.angle    = 0.f;
    drawable.repeatX  = SCR_WIDTH  / 128 + 1;
    drawable.repeatY  = SCR_HEIGHT / 128 + 2;
    drawable.priority = 0;
    floor->AddComponent(new ComponentRenderable(floor, drawable, &graphicsEngine, true));
    entities.push_back(floor);
}

void Game::LoadPlayer() {
    player = new Entity(this);
    // Transform
    vec2  pos    = vmake(SCR_WIDTH / 2, SCR_HEIGHT / 20);
    float radius = 25.f;
    float angle  = 90.f;
    player->AddComponent(new ComponentTransform(player, pos,
        radius, angle, 6.f, false));
    // Graphics
    GraphicsEngine::Drawable drawable;
    drawable.sprite   = GraphicsEngine::Sprite::PLAYER;
    drawable.pos      = pos;
    drawable.size     = vmake(radius * 2, radius * 2);
    drawable.angle    = angle;
    drawable.priority = 2;
    player->AddComponent(new ComponentRenderable(player, drawable,
        &graphicsEngine, true));
    // Graphics (SlashFX)
    GraphicsEngine::Drawable drawableFX = drawable;
    drawableFX.sprite = GraphicsEngine::Sprite::SLASH;
    drawableFX.priority = 3;
    player->AddComponent(new ComponentRenderableFX(player,
        drawableFX, &graphicsEngine, false));
    // Collider
    player->AddComponent(new ComponentCollider(player, &physicsEngine,
        PhysicsEngine::Collider(pos, radius, PhysicsEngine::ColliderID::PLAYER,
            player)));

    player->AddComponent(new ComponentPlayer(player, 25.f, 10));
    entities.push_back(player);
}

void Game::LoadLevelJSON(Difficulty diff) {
    // Read file
    FILE* fp = fopen("../data/levels.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);
    assert(d.IsObject());
    fclose(fp);

    // Parse
    rapidjson::Value jsonEnemies; // Array of enemies
    if      (diff == Difficulty::EASY) {
        assert(d.HasMember("easy"));
        assert(d["easy"]["enemies"].IsArray());
        jsonEnemies = d["easy"]["enemies"];
    }
    else if (diff == Difficulty::NORMAL) {
        assert(d.HasMember("normal"));
        assert(d["normal"]["enemies"].IsArray());
        jsonEnemies = d["normal"]["enemies"];
    }
    else if (diff == Difficulty::HARD) {
        assert(d.HasMember("hard"));
        assert(d["hard"]["enemies"].IsArray());
        jsonEnemies = d["hard"]["enemies"];
    }
    // Enemies
    for (rapidjson::SizeType i = 0; i < jsonEnemies.Size(); ++i) {
        float posX  = jsonEnemies[i]["posX"].GetFloat();
        float posY  = jsonEnemies[i]["posY"].GetFloat();
        float angle = jsonEnemies[i]["angle"].GetFloat();
        LoadEnemy(posX, posY, angle);
    }
}

void Game::LoadEnemy(float posX, float posY, float angle) {
    Entity* enemy = new Entity(this);
    // Transform
    vec2 pos = vmake(posX, posY);
    float radius = 25.f;
    float speed  = 6.f;
    enemy->AddComponent(new ComponentTransform(enemy, pos,
        radius, angle, speed, true));
    // Graphics
    GraphicsEngine::Drawable drawable;
    drawable.sprite   = GraphicsEngine::Sprite::ENEMY;
    drawable.pos      = pos;
    drawable.size     = vmake(radius * 2, radius * 2);
    drawable.angle    = angle;
    drawable.priority = 2;
    enemy->AddComponent(new ComponentRenderable(enemy, drawable,
        &graphicsEngine, true));
    // Enemy
    size_t timeToShoot = 24;
    enemy->AddComponent(new ComponentEnemy(enemy, timeToShoot,
        pos, angle));
    // Collider
    enemy->AddComponent(new ComponentCollider(enemy, &physicsEngine,
        PhysicsEngine::Collider(pos, radius, PhysicsEngine::ColliderID::ENEMY,
            enemy)));
    
    ++enemiesLeft;
    entities.push_back(enemy);
}
// ================================================================

// STATE ==========================================================
void Game::ProcessInput(Action action) {
    MessageMove     * moveMsg   = nullptr;
    MessageSetAngle * turnMsg   = nullptr;
    MessageAttack   * attackMsg = nullptr;
    switch (action) {
    case Action::SLASH:
        attackMsg = new MessageAttack();
        player->ReceiveMessage(attackMsg);
        break;
    case Action::MOVE_U:
        moveMsg = new MessageMove();
        turnMsg = new MessageSetAngle();
        moveMsg->direction = MessageMove::Dir::UP;
        turnMsg->angle     = 90.f;
        break;
    case Action::MOVE_D:
        moveMsg = new MessageMove();
        turnMsg = new MessageSetAngle();
        moveMsg->direction = MessageMove::Dir::DOWN;
        turnMsg->angle     = -90.f;
        break;
    case Action::MOVE_L:
        moveMsg = new MessageMove();
        turnMsg = new MessageSetAngle();
        moveMsg->direction = MessageMove::Dir::LEFT;
        turnMsg->angle     = 179.f;
        break;
    case Action::MOVE_R:
        moveMsg = new MessageMove();
        turnMsg = new MessageSetAngle();
        moveMsg->direction = MessageMove::Dir::RIGHT;
        turnMsg->angle     = 0.f;
        break;
    }
    if (moveMsg) player->ReceiveMessage(moveMsg);
    if (turnMsg) player->ReceiveMessage(turnMsg);
    delete moveMsg;
    delete turnMsg;
    delete attackMsg;
}

void Game::Run() {
    // Remove entities
    for (auto entity : entitiesToRemove) {
        entities.erase(std::remove(entities.begin(), entities.end(), entity),
            entities.end());
    }
    entitiesToRemove.clear();
    
    // Update entities
    for (auto entity : entities)
        entity->Run();
    physicsEngine.Run();
    physicsEngine.Clear();

    // Add entities
    for (auto entity : entitiesToAdd)
        entities.push_back(entity);
    entitiesToAdd.clear();
}

void Game::Render() {
	graphicsEngine.Draw();
	graphicsEngine.ClearSprites();
}
// ================================================================

// LEVEL ==========================================================
bool Game::IsLevelComplete() {
    return enemiesLeft > 0 ? false : true;
}

void Game::AddBullet(vec2 pos, float angle) {
    Entity* bullet = new Entity(this);
    // Transform
    float radius = 12.f;
    float speed  = 6.f;
    bullet->AddComponent(new ComponentTransform(bullet, pos,
        radius, angle, speed, true));
    // Graphics
    GraphicsEngine::Drawable drawable;
    drawable.sprite   = GraphicsEngine::Sprite::BULLET;
    drawable.pos      = pos;
    drawable.size     = vmake(radius * 2, radius * 2);
    drawable.angle    = angle;
    drawable.priority = 2;
    bullet->AddComponent(new ComponentRenderable(bullet, drawable,
        &graphicsEngine, true));
    // Collider
    bullet->AddComponent(new ComponentCollider(bullet, &physicsEngine,
        PhysicsEngine::Collider(pos, radius, PhysicsEngine::ColliderID::BULLET,
            bullet)));

    bullet->AddComponent(new ComponentBullet(bullet, angle));
    entitiesToAdd.push_back(bullet);
}

void Game::DeleteEntity(Entity* entity) {
    entitiesToRemove.push_back(entity);
}

void Game::KillEnemy(Entity* enemy, const vec2 pos) {
    DeleteEntity(enemy);
    --enemiesLeft;

    // Blood FX
    GraphicsEngine::Drawable drawableFX;
    drawableFX.size   = vmake(70.f, 70.f);
    drawableFX.pos    = pos;
    drawableFX.sprite = GraphicsEngine::Sprite::BLOOD;
    drawableFX.priority = 1;

    Entity* blood = new Entity(this);
    blood->AddComponent(new ComponentRenderableFX(blood,
        drawableFX, &graphicsEngine, true));
    entities.push_back(blood);
}
// ================================================================
