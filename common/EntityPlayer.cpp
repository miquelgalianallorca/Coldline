#include "EntityPlayer.h"
#include "globals.h"
#include "Game.h"

EntityPlayer::EntityPlayer(vec2 _pos, float _vel, GLuint _gfx, float _radius, float _angle, bool _alive,
    float _playerRange, GLuint _gfxSlash, std::vector<Entity*>& _enemies) :
    Entity(_pos, _vel, _gfx, _radius, _angle, _alive),
    playerRange(_playerRange),
    slashTimer(0),
    gfxSlash(_gfxSlash),
    enemies(_enemies)
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
        for (auto enemy : enemies) {
            if (enemy->GetAlive() && Game::Distance(pos, enemy->GetPos()) < playerRange) {
                enemy->SetAlive(false);
                ++numDead; //Fixing here... TO DO
            }
        }
        // All dead: level cleared
        if (numDead == enemies.size()) levelComplete = true;
    }
    if (slashTimer > 0) --slashTimer;
}

void EntityPlayer::Render() {
    CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfx);
    if (slashTimer > 0)
        CORE_RenderCenteredRotatedSprite(pos, vmake(radius * 2.f, radius * 2.f), angle, gfxSlash);
}