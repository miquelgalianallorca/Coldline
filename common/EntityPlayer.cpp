#include "EntityPlayer.h"
#include "globals.h"
#include "Game.h"

EntityPlayer::EntityPlayer(vec2 _pos, float _vel, GLuint _gfx, float _radius, float _angle, bool _alive,
    float _playerRange, GLuint _gfxSlash) :
    Entity(_pos, _vel, _gfx, _radius, _angle, _alive),
    playerRange(_playerRange),
    slashTimer(0),
    gfxSlash(_gfxSlash)
{}

void EntityPlayer::Run() {
    // Move
    vec2 newPos = pos;
    if (SYS_KeyPressed(SYS_KEY_UP))    { newPos = vadd(newPos, vmake(0,  vel)); angle = 90.f;  }
    if (SYS_KeyPressed(SYS_KEY_DOWN))  { newPos = vadd(newPos, vmake(0, -vel)); angle = -90.f; }
    if (SYS_KeyPressed(SYS_KEY_LEFT))  { newPos = vadd(newPos, vmake(-vel, 0)); angle = 179.f; }
    if (SYS_KeyPressed(SYS_KEY_RIGHT)) { newPos = vadd(newPos, vmake(vel,  0)); angle = 0.f;   }
    pos = newPos;
    // Slash
    if (SYS_MouseButonPressed(SYS_MB_LEFT)) {
        slashTimer = 10;
        game->CheckKill(pos, playerRange);
    }
    if (slashTimer > 0) --slashTimer;
}

void EntityPlayer::Render() {
    CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfx);
    if (slashTimer > 0)
        CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfxSlash);
}