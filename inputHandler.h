#include <iostream>
#include <sstream>
#include "string"

namespace InputHandler
{
    std::istringstream Input(const std::string prompt);

    template<typename T>
    int InputInteger(const std::string prompt, T&& additionalValidation = [](int){return true;})
    {
        std::istringstream input = Input(prompt);
        int v;
        if ((input >> v) && (input >> std::ws).eof() && additionalValidation(v))
            return v;
        throw std::runtime_error("Unexpected input.");
    }
}