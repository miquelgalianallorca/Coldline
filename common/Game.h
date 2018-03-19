#pragma once

#include "stdafx.h"
#include "GraphicsEngine.h"

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

    void  Run();
    void  Render();
    void  ReceiveMessage(Message *msg);
    
	bool  IsLevelComplete();
	bool  IsPlayerDead();

	float Distance(const vec2 &pos1, const vec2 &pos2);
    void  CheckKill(const vec2& playerPos, const float playerRange);
    void  ProcessInput(Action action);
    void  SetSlashing(bool value);
    void  AddBullet(vec2 pos, float angle);

private:
    // Game Utilities
    void LoadPlayer();
    void LoadFloor();
    void LoadLevel();
	void LoadLevelJSON(Difficulty diff);

    // Entities
    std::vector<Entity*> entities;
	std::vector<Entity*> entitiesToAdd;
	std::vector<Entity*> entitiesToRemove;

    //std::vector<Entity*> enemies;
    //std::vector<Entity*> bullets;
    Entity *player;

    // Level
    size_t numDead;
    bool   levelComplete;
    bool   playerSlashing;

    GraphicsEngine graphicsEngine;
};