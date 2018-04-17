#include "Button.h"

// BUTTON =======================================================
Button::Button(vec2 _pos, std::string _text,
    std::function<void()> _executeFunction) :
    pos(_pos),
    text(_text),
    executeFunction(_executeFunction)
{
    activeText  = text + " - ";
    currentText = text;
}

void Button::SetActive(bool value) {
    isActive = value;
    if (value) currentText = activeText;
    else       currentText = text;
}

void Button::Render() {
    FONT_DrawString(pos, currentText.data());
}

void Button::Execute() {
    if (executeFunction)
        executeFunction();
}
// ==============================================================

