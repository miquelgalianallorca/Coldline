#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {
    texPlayer = CORE_LoadPNG("data/survivor.png",  false);
    texFloor  = CORE_LoadPNG("data/tilefloor.png", false);
    texEnemy  = CORE_LoadPNG("data/rifleman.png",  false);
    texBlood  = CORE_LoadPNG("data/blood.png",     false);
    texSlash  = CORE_LoadPNG("data/slash.png",     false);
}

GraphicsEngine::~GraphicsEngine() {
    CORE_UnloadPNG(texPlayer);
    CORE_UnloadPNG(texFloor);
    CORE_UnloadPNG(texEnemy);
    CORE_UnloadPNG(texBlood);
    CORE_UnloadPNG(texSlash);
}

void GraphicsEngine::Draw(Sprite sprite, vec2 pos, vec2 size, float angle) {
    GLuint texID;
    switch (sprite) {
        case Sprite::BLOOD:  texID = texBlood;  break;
        case Sprite::ENEMY:  texID = texEnemy;  break;
        case Sprite::FLOOR:  texID = texFloor;  break;
        case Sprite::PLAYER: texID = texPlayer; break;
        case Sprite::SLASH:  texID = texSlash;  break;
    }
    CORE_RenderCenteredRotatedSprite(pos, size, angle, texID);
}