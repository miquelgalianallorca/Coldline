#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"

struct Entity {
  vec2   pos;
  float  vel;
  GLuint gfx;
  float  radius;
  float  angle;
  bool   alive;
};

void LoadLevel(std::vector<Entity> &enemies, GLuint texEnemy) {
    Entity enemy1;
    enemy1.pos = vmake(30.f, 100.f);
    enemy1.vel = 8.f;
    enemy1.radius = 25.f;
    enemy1.gfx = texEnemy;
    enemy1.angle = 0.f;
    enemies.push_back(enemy1);
    Entity enemy2;
    enemy2.pos = vmake(100.f, 400.f);
    enemy2.vel = 8.f;
    enemy2.radius = 25.f;
    enemy2.gfx = texEnemy;
    enemy2.angle = 0.f;
    enemies.push_back(enemy2);
    Entity enemy3;
    enemy3.pos = vmake(450.f, 350.f);
    enemy3.vel = 8.f;
    enemy3.radius = 25.f;
    enemy3.gfx = texEnemy;
    enemy3.angle = -90.f;
    enemies.push_back(enemy3);
}

float Distance(const vec2 &pos1, const vec2 &pos2) {
    vec2 dir = vmake(pos2.x - pos1.x, pos2.y - pos1.y);
    float dist = sqrtf(dir.x * dir.x + dir.y * dir.y);
    
   /* char buffer[100];
    sprintf_s(buffer, "Dist: %f\n", dist);
    OutputDebugStringA(buffer);*/
    
    return dist;
}

int Main(void) {
  //FONT_Init();

  // Load textures
  GLuint texPlayer = CORE_LoadPNG("data/survivor.png",  false);
  GLuint texFloor  = CORE_LoadPNG("data/tilefloor.png", false);
  GLuint texEnemy  = CORE_LoadPNG("data/rifleman.png",  false);
  GLuint texBlood  = CORE_LoadPNG("data/blood.png",     false);
  GLuint texSlash  = CORE_LoadPNG("data/slash.png",     false);

  // Init game state
  Entity player;
  player.pos = vmake(SCR_WIDTH / 2, SCR_HEIGHT / 20);
  player.vel = 6.f;
  player.radius = 25.f;
  player.gfx = texPlayer;
  player.angle = 90.f;

  float playerRange = 50.f;
  int slashTimer = 0;

  std::vector<Entity> bullets;
  std::vector<Entity> enemies;
  LoadLevel(enemies, texEnemy);

  // Set up rendering
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
  glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!SYS_GottaQuit()) {
    // Render ===========================================================================================
    glClear( GL_COLOR_BUFFER_BIT );

    // Render background
    for (int i = 0; i <= SCR_WIDTH/128; i++)
      for (int j = 0; j <= SCR_HEIGHT/128; j++)
        CORE_RenderCenteredSprite(vmake(i * 128.f + 64.f, j * 128.f + 64.f), vmake(128.f, 128.f), texFloor);

    //Render enemies
    for (auto enemy : enemies) {
        if (enemy.alive)
            CORE_RenderCenteredRotatedSprite(enemy.pos, vmake(enemy.radius * 2.f, enemy.radius * 2.f), enemy.angle, enemy.gfx);
        else
            CORE_RenderCenteredRotatedSprite(enemy.pos, vmake(enemy.radius * 2.f, enemy.radius * 2.f), enemy.angle, texBlood);
    }
    //Render player
    CORE_RenderCenteredRotatedSprite(player.pos, vmake(player.radius * 2.f, player.radius * 2.f), player.angle, player.gfx);

    //Render effects
    if (slashTimer > 0) {
        CORE_RenderCenteredRotatedSprite(player.pos, vmake(player.radius * 2.f, player.radius * 2.f), player.angle, texSlash);
    }

    SYS_Show();
    // ==================================================================================================


    // Run ==============================================================================================
    // Move
    vec2 newpos = player.pos;
    if (SYS_KeyPressed(SYS_KEY_UP))   { newpos = vadd(newpos, vmake(0, player.vel));  player.angle = 90.f;  }
    if (SYS_KeyPressed(SYS_KEY_DOWN)) { newpos = vadd(newpos, vmake(0, -player.vel)); player.angle = -90.f; }
    if (SYS_KeyPressed(SYS_KEY_LEFT)) { newpos = vadd(newpos, vmake(-player.vel, 0)); player.angle = 179.f; }
    if (SYS_KeyPressed(SYS_KEY_RIGHT)){ newpos = vadd(newpos, vmake(player.vel,  0)); player.angle = 0.f;   }
    player.pos = newpos;
   
    // Slash
    if (SYS_MouseButonPressed(SYS_MB_LEFT)) {
        slashTimer = 10;
        for (auto enemy : enemies) {
            if (Distance(player.pos, enemy.pos) < playerRange)
                enemy.alive = false;
        }
    }
    if (slashTimer > 0) {
        --slashTimer;
    }
    // ==================================================================================================
   
    // Keep system running
    SYS_Pump();
    SYS_Sleep(17);
  }

  CORE_UnloadPNG(texPlayer);
  //FONT_End();

  return 0;
}
