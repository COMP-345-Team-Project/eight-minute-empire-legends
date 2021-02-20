#pragma once
#include <exception>
#include <iostream>

class MapLoaderException : public std::exception
{
private:
   std::string errorMessage;
public:
    MapLoaderException(const std::string& msg);
    const char* what() const throw();
};