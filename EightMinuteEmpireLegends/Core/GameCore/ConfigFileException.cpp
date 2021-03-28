#pragma once

#include "../pch.h"

#include "ConfigFileException.h"

ConfigFileException::ConfigFileException(const std::string& msg) : errorMessage(msg) {}

const char* ConfigFileException::what() const throw ()
{
    return errorMessage.c_str();
}