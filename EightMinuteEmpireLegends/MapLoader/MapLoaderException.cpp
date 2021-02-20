#pragma once
#include "MapLoaderException.h"
#include <iostream>

MapLoaderException::MapLoaderException(const std::string& msg) : errorMessage(msg){}

const char* MapLoaderException::what() const throw ()
{
    return errorMessage.c_str();
}