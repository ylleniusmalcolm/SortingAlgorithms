#pragma once
#include <iostream>
#include <sstream>
#include "string"

namespace InputHandler
{
    std::istringstream Input(const std::string prompt);

    template <typename T, typename U>
    T InputT(const std::string prompt, U&& additionalValidation = [](T){return true;}, std::string additionalValidationFailText = "")
    {
        std::istringstream input = Input(prompt);
        T v;
        if (!((input >> v) && (input >> std::ws).eof()))
            throw std::runtime_error("Input cannot be parsed to correct type.");
        else if (!additionalValidation(v))
            throw std::runtime_error(additionalValidationFailText);
        
        return v;    
    }
}