#pragma once

#include "../pch.h"

class GameBuilderException : public std::exception
{
private:
    std::string errorMessage;
public:
    GameBuilderException(const std::string& msg);
    const char* what() const throw();
};
