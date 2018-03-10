#include "Game.h"
#include "Component.h"
#include "ComponentRenderable.h"
#include "EntityPlayer.h"
#include "EntityEnemy.h"
#include "EntityBullet.h"
#include "Message.h"
#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

Game::Game(Difficulty diff) :
    numDead(0),
    levelComplete(false),
    playerSlashing(false)
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
    enemies.clear();
    bullets.clear();
}

void Game::LoadFloor() {
    Entity *floor = new Entity();
    GraphicsEngine::Drawable drawable;
    drawable.sprite   = GraphicsEngine::Sprite::FLOOR;
    drawable.pos      = vmake(0.f, 0.f);
    drawable.size     = vmake(128.f, 128.f);
    drawable.angle    = 0.f;
    drawable.repeatX  = SCR_WIDTH  / 128 + 1;
    drawable.repeatY  = SCR_HEIGHT / 128 + 2;
    drawable.priority = 0;
    floor->AddComponent(new ComponentRenderable(floor, drawable, &graphicsEngine));
    entities.push_back(floor);
}

void Game::LoadPlayer() {
    player = new Entity();
    vec2  playerPos    = vmake(SCR_WIDTH / 2, SCR_HEIGHT / 20);
    float playerRadius = 25.f;
    float playerAngle  = 90.f;
    player->AddComponent(new ComponentTransform(player, playerPos, playerRadius, playerAngle, 6.f));
    
    GraphicsEngine::Drawable drawable;
    drawable.sprite   = GraphicsEngine::Sprite::PLAYER;
    drawable.pos      = playerPos;
    drawable.size     = vmake(playerRadius * 2, playerRadius * 2);
    drawable.angle    = playerAngle;
    drawable.priority = 1;
    player->AddComponent(new ComponentRenderable(player, drawable, &graphicsEngine));

    entities.push_back(player);
}

void Game::Render() {
	graphicsEngine.Draw();
	graphicsEngine.ClearSprites();

    //================================================================= Entities
    // Render enemies
    //for (auto enemy : enemies) {
    //    if (enemy->GetAlive())
    //        graphicsEngine.Draw(GraphicsEngine::Sprite::ENEMY, enemy->GetPos(),
    //            vmake(enemy->GetRadius() * 2, enemy->GetRadius() * 2), enemy->GetAngle());
    //    else
    //        graphicsEngine.Draw(GraphicsEngine::Sprite::BLOOD, enemy->GetPos(),
    //            vmake(enemy->GetRadius() * 2, enemy->GetRadius() * 2), enemy->GetAngle());
    //}

    //// Render player
    //graphicsEngine.Draw(GraphicsEngine::Sprite::PLAYER, player->GetPos(),
    //    vmake(player->GetRadius() * 2, player->GetRadius() * 2), player->GetAngle());
    //if (playerSlashing)
    //    graphicsEngine.Draw(GraphicsEngine::Sprite::SLASH, player->GetPos(),
    //        vmake(player->GetRadius() * 2, player->GetRadius() * 2), player->GetAngle());
    //
    //// Render bullets
    //for (auto bullet : bullets) {
    //    graphicsEngine.Draw(GraphicsEngine::Sprite::BULLET, bullet->GetPos(),
    //        vmake(bullet->GetRadius() * 2, bullet->GetRadius() * 2), bullet->GetAngle());
    //}
    //===========================================================================
}

void Game::Run() {
    for (auto entity : entities) {
        entity->Run();
    }
    // Can't add to iterator while iterating, so bullets are added later
    for (auto bullet : bullets) {
        if (std::find(entities.begin(), entities.end(), bullet) == entities.end()) {
            entities.push_back(bullet);
        }
    }
}

bool Game::IsLevelComplete() { return levelComplete; }

void Game::LoadLevel() {
    Entity *enemy1 = new EntityEnemy(vmake(30.f,  100.f), 8.f, 25.f, 0.f, true, 20);
    Entity *enemy2 = new EntityEnemy(vmake(100.f, 400.f), 8.f, 25.f, -90.f, true, 20);
    Entity *enemy3 = new EntityEnemy(vmake(450.f, 350.f), 8.f, 25.f, 179.f, true, 20);
    entities.push_back(enemy1);
    entities.push_back(enemy2);
    entities.push_back(enemy3);
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
}

void Game::LoadLevelJSON(Difficulty diff) {
	// Read file
	FILE* fp = fopen("data/levels.json", "rb"); // non-Windows use "r"
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
		float posX = jsonEnemies[i]["posX"].GetFloat();
		float posY = jsonEnemies[i]["posY"].GetFloat();
		float angle = jsonEnemies[i]["angle"].GetFloat();
		Entity *enemy = new EntityEnemy(vmake(posX, posY), 8.f, 25.f, angle, true, 20);
		enemies.push_back(enemy);
		entities.push_back(enemy);
	}
}

float Game::Distance(const vec2 &pos1, const vec2 &pos2) {
    vec2 dir = vmake(pos2.x - pos1.x, pos2.y - pos1.y);
    return sqrtf(dir.x * dir.x + dir.y * dir.y);
}

void Game::CheckKill(const vec2& playerPos, const float playerRange) {
    //for (auto enemy : enemies) {
    //    if (enemy->GetAlive() && Distance(playerPos, enemy->GetPos()) < playerRange) {
    //        enemy->SetAlive(false);
    //        ++numDead;
    //    }
    //}
    //// All dead: level cleared
    //if (numDead == enemies.size()) levelComplete = true;
}

void Game::ProcessInput(Action action) {
    MessageMove     * moveMsg = new MessageMove();
    MessageSetAngle * turnMsg = new MessageSetAngle();
    switch (action) {
        case Action::MOVE_U:
            moveMsg->direction = MessageMove::Dir::UP;
            turnMsg->angle     = 90.f;
            break;
        case Action::MOVE_D:
            moveMsg->direction = MessageMove::Dir::DOWN;
            turnMsg->angle     = -90.f;
            break;
        case Action::MOVE_L:
            moveMsg->direction = MessageMove::Dir::LEFT;
            turnMsg->angle     = 179.f;
            break;
        case Action::MOVE_R:
            moveMsg->direction = MessageMove::Dir::RIGHT;
            turnMsg->angle     = 0.f;
            break;
        case Action::SLASH:
            MessageAttack * msgAtt = new MessageAttack();
            player->ReceiveMessage(msgAtt);
            delete msgAtt;
            break;
    }
    player->ReceiveMessage(moveMsg);
    player->ReceiveMessage(turnMsg);
    delete moveMsg;
    delete turnMsg;
}

void Game::SetSlashing(bool value) { playerSlashing = value; }

void Game::AddBullet(vec2 pos, float angle) {
    Entity *bullet = new EntityBullet(pos, 20.f, 15.f, angle, true);
    bullets.push_back(bullet);
}

bool Game::IsPlayerDead() {
	/*for (auto bullet : bullets) {
		vec2 posP = player->GetPos();
		vec2 posB = bullet->GetPos();
		float rad = player->GetRadius() + bullet->GetRadius();
		if (Distance(posP, posB) < rad)
			return true;
	}*/
	return false;
}