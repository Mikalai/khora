#pragma once

#include "IUserInput.h"
#include "ConsoleUserInput.h"

IUserInput* g_userInput;

IUserInput& ui() {
    return *g_userInput;
}

void SetUI(IUserInput* value) {
    g_userInput = value;
}
