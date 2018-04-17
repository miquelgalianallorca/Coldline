#include "Menu.h"
#include "globals.h"
#include "stdafx.h"
#include "swalib/sys.h"
#include "swalib/core.h"
#include "swalib/font.h"

// DIFFICULTY ======================================================
void DifficultyMenu::ProcessInput(const MenuManager::Action &action) {
    if (action == MenuManager::Action::OK)
        menuManager->SetChangeState(true);
}

void DifficultyMenu::Run() {
    // TO DO: Update active button
    /*if (SYS_KeyPressed(SYS_1))      menuManager->SetChangeState(true);
    else if (SYS_KeyPressed(SYS_2)) menuManager->SetChangeState(true);
    else if (SYS_KeyPressed(SYS_3)) menuManager->SetChangeState(true);*/
}

void DifficultyMenu::Render() {
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 + 50), "COLDLINE");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 50), "1. EASY");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 70), "2. NORMAL");
    FONT_DrawString(vmake(SCR_WIDTH / 2 - 80, SCR_HEIGHT / 2 - 90), "3. HARD");
}
// =================================================================

