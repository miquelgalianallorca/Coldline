#include "Menu.h"
#include "Button.h"
#include "globals.h"

Menu::Menu(vec2 _pos, std::string _title) :
    pos(_pos),
    title(_title),
    activeButtonIndex(0)
{}

Menu::~Menu() {
    for (auto button : buttons)
        delete button;
    buttons.clear();
}
