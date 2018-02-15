#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {
    texPlayer = CORE_LoadPNG("data/survivor.png",  false);
    texFloor  = CORE_LoadPNG("data/tilefloor.png", false);
    texEnemy  = CORE_LoadPNG("data/rifleman.png",  false);
    texBlood  = CORE_LoadPNG("data/blood.png",     false);
    texSlash  = CORE_LoadPNG("data/slash.png",     false);
    texBullet = CORE_LoadPNG("data/bullet.png",    false);
}

GraphicsEngine::~GraphicsEngine() {
    CORE_UnloadPNG(texPlayer);
    CORE_UnloadPNG(texFloor);
    CORE_UnloadPNG(texEnemy);
    CORE_UnloadPNG(texBlood);
    CORE_UnloadPNG(texSlash);
    CORE_UnloadPNG(texBullet);
}

void GraphicsEngine::Draw(Sprite sprite, vec2 pos, vec2 size, float angle) {
    GLuint texID;
    switch (sprite) {
        case Sprite::BLOOD:  texID = texBlood;  break;
        case Sprite::ENEMY:  texID = texEnemy;  break;
        case Sprite::FLOOR:  texID = texFloor;  break;
        case Sprite::PLAYER: texID = texPlayer; break;
        case Sprite::SLASH:  texID = texSlash;  break;
        case Sprite::BULLET: texID = texBullet; break;
    }
    CORE_RenderCenteredRotatedSprite(pos, size, angle, texID);
}

void GraphicsEngine::RegisterSprite(Drawable *drawable) {
	registeredDrawables.push_back(drawable);
}

void GraphicsEngine::ClearSprites() { registeredDrawables.clear(); }

void GraphicsEngine::Draw() {
	for (auto drawable : registeredDrawables) {
		GLuint texID;
		switch (drawable->sprite) {
			case Sprite::BLOOD:  texID = texBlood;  break;
			case Sprite::ENEMY:  texID = texEnemy;  break;
			case Sprite::FLOOR:  texID = texFloor;  break;
			case Sprite::PLAYER: texID = texPlayer; break;
			case Sprite::SLASH:  texID = texSlash;  break;
			case Sprite::BULLET: texID = texBullet; break;
		}
		for (int i = 0; i < drawable->repeatX; ++i) {
			for (int j = 0; j < drawable->repeatY; ++j) {
				vec2 offset  = vmake(i * drawable->size.x, j * drawable->size.y);
				vec2 realPos = vadd(drawable->pos, offset);
				CORE_RenderCenteredRotatedSprite(realPos, drawable->size, drawable->angle, texID);
			}
		}		
	}
}

