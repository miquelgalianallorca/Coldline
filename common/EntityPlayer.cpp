#include "EntityPlayer.h"
#include "globals.h"
#include "Game.h"

EntityPlayer::EntityPlayer(vec2 _pos, float _vel, GLuint _gfx, float _radius, float _angle, bool _alive,
    float _playerRange, GLuint _gfxSlash) :
    Entity(_pos, _vel, _gfx, _radius, _angle, _alive),
    playerRange(_playerRange),
    slashTimer(0),
    gfxSlash(_gfxSlash)
{
    entityType = EntityType::PLAYER;
}

void EntityPlayer::Run() {
    if (slashTimer > 0)
        --slashTimer;
}

void EntityPlayer::Render() {
    CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfx);
    if (slashTimer > 0)
        CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfxSlash);
}

void EntityPlayer::Move(vec2 newPos, float _angle) {
    angle = _angle;
    pos   = newPos;
}

void EntityPlayer::Attack() {
    slashTimer = 10;
    game->CheckKill(pos, playerRange);
}