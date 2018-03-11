#include "EntityPlayer.h"
#include "globals.h"
#include "Game.h"

EntityPlayer::EntityPlayer(vec2 _pos, float _vel, float _radius, float _angle, bool _alive,
    float _playerRange) :
    //Entity(_pos, _vel, _radius, _angle, _alive),
    playerRange(_playerRange),
    slashTimer(0),
    Entity(nullptr)
{
    //entityType = EntityType::PLAYER;
}

void EntityPlayer::Run() {
    /*if (slashTimer > 0) {
        --slashTimer;
        if (slashTimer == 0) game->SetSlashing(false);
    }*/
}

void EntityPlayer::Move(vec2 newPos, float _angle) {
    /*angle = _angle;
    pos   = newPos;*/
}

void EntityPlayer::Attack() {
    /*slashTimer = 10;
    game->CheckKill(pos, playerRange);
    game->SetSlashing(true);*/
}