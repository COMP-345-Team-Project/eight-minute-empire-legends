#pragma once

#include "../pch.h"

#include "GameBuilderException.h"

GameBuilderException::GameBuilderException(const std::string& msg) : errorMessage(msg) {}

const char* GameBuilderException::what() const throw ()
{
    return errorMessage.c_str();
}