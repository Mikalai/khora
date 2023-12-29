#include "ConsoleUserInput.h"
#include "IUserInput.h"

IUserInput* g_userInput;

IUserInput& ui() { return *g_userInput; }

void SetUI(IUserInput* value) { g_userInput = value; }
