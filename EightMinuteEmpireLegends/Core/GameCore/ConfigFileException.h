#pragma once

#include "../pch.h"

class ConfigFileException : public std::exception
{
private:
    std::string errorMessage;
public:
    ConfigFileException(const std::string& msg);
    const char* what() const throw();
};
