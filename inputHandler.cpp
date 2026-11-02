#include "inputHandler.h"

std::istringstream InputHandler::Input(const std::string prompt)
{
    std::cout << prompt;
    std::string inputString;
    std::getline(std::cin, inputString);
    return std::istringstream(inputString);
}