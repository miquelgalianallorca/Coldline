#pragma once

#include "stdafx.h"
#include "GraphicsEngine.h"
#include "PhysicsEngine.h"

class  Entity;
class  EntityPlayer;
struct Message;

class Game {
public:
    enum class Action     { MOVE_L, MOVE_U, MOVE_R, MOVE_D, SLASH };
    enum class Direction  { LEFT,   UP,     RIGHT,  DOWN          };
	enum class Difficulty { EASY,   NORMAL, HARD                  };
    
	Game(Difficulty diff);
    ~Game();

    // STATE =======================================
    void ProcessInput(Action action);
    void Run();
    void Render();
    // =============================================

    // LEVEL =======================================
	bool IsLevelComplete();
    bool IsPlayerDead() { return isPlayerDead; }
	void AddBullet(vec2 pos, float angle);
    void DeleteEntity(Entity* entity);
    void KillPlayer();
    void KillEnemy(Entity* enemy, const vec2 pos);
    // =============================================

    void ToggleInGameMenu();
    bool GetIsInGameMenuOpen() const { return isInGameMenuOpen; }

private:
    // LOADING =====================================
    void LoadPlayer();
    void LoadFloor();
	void LoadLevelJSON(Difficulty diff);
    void LoadEnemy(float posX, float posY, float angle);
    // =============================================

    // ECS =========================================
    std::vector<Entity*> entities;
	std::vector<Entity*> entitiesToAdd;
	std::vector<Entity*> entitiesToRemove;
    Entity *player;
    
    GraphicsEngine graphicsEngine;
    PhysicsEngine  physicsEngine;
    // =============================================

    // Level =======================================
    size_t enemiesLeft;
    bool   isPlayerDead;
    // =============================================

    bool isInGameMenuOpen;
};