#pragma once
#include "../pch.h"

#include "MapLoaderException.h"

MapLoaderException::MapLoaderException(const std::string& msg) : errorMessage(msg){}

const char* MapLoaderException::what() const throw ()
{
    return errorMessage.c_str();
}