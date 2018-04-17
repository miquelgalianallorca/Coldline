#pragma once

#include "stdafx.h"
#include "swalib/sys.h"
#include "swalib/core.h"
#include "swalib/font.h"
#include <functional>

class Button {
public:
    Button(vec2 _pos, std::string _text,
        std::function<void()> _executeFunction);
    ~Button() {}

    bool GetActive() const { return isActive; }
    void SetActive(bool value);

    void Render();
    void Execute();

private:
    bool isActive;
    vec2 pos;
    std::string text;
    std::string activeText;
    std::string currentText;
    std::function<void()> executeFunction;
};
