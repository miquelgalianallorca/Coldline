#include "Button.h"
#include "globals.h"
#include "GraphicsEngine.h"

// BUTTON =======================================================
Button::Button(vec2 _pos, std::string _text,
    std::function<void()> _executeFunction) :
    pos(_pos),
    executeFunction(_executeFunction)
{
    inactiveText = "   " + _text;
    activeText   = " - " + _text;
    currentText = inactiveText;
}

void Button::SetActive(bool value) {
    isActive = value;
    if (value) currentText = activeText;
    else       currentText = inactiveText;
}

void Button::Render() {
    graphicsEngine->DrawTextLine(pos, currentText.data());
}

void Button::Execute() {
    if (executeFunction)
        executeFunction();
}
// ==============================================================

