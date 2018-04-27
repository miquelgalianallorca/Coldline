#include "stdafx.h"
#include "swalib\sys.h"
#include "swalib\core.h"
#include "swalib\font.h"

#include "globals.h"
#include "GraphicsEngine.h"
#include "StateManager.h"

void SetupRender();

// Definition of externals (globals.h)
StateManager*   stateManager   = nullptr;
Game*           game           = nullptr;
MenuManager*    menuManager    = nullptr;
GraphicsEngine* graphicsEngine = nullptr;

int Main(void) {
    FONT_Init();
    SetupRender();

    graphicsEngine = new GraphicsEngine();
    stateManager = new StateManager();
    
    while (!SYS_GottaQuit()) {
        glClear(GL_COLOR_BUFFER_BIT);
        stateManager->Input();
        stateManager->Run();
        stateManager->Render();
        SYS_Show();
        // Keep system running
        SYS_Pump();
        SYS_Sleep(17);
    }    
    FONT_End();
    return 0;
}

void SetupRender() {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
    glClearColor(0.0f, 0.1f, 0.3f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
