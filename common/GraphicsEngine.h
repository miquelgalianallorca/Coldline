#pragma once

#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"

class GraphicsEngine {
public:
    enum class Sprite {
        PLAYER,
        ENEMY,
        FLOOR,
        SLASH,
        BLOOD,
        BULLET,
        MENU_BG
    };

	struct Drawable {
		Sprite sprite;
		vec2   pos;
		vec2   size;
		float  angle;
		int    repeatX = 1;
		int    repeatY = 1;
        int    priority;
	};

    GraphicsEngine();
    ~GraphicsEngine();

	void RegisterSprite(Drawable *drawable);
	void ClearSprites();
    void Draw();

private:
    GLuint texPlayer;
    GLuint texFloor;
    GLuint texEnemy;
    GLuint texBlood;
    GLuint texSlash;
    GLuint texBullet;
    GLuint texMenuBg;
	
	std::vector<Drawable*> registeredDrawables;
    void OrderDrawables();
};