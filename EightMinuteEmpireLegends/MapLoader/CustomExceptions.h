#pragma once
#include <iostream>

class InvalidFileFormatException : public std::runtime_error
{
    private:
        string what_message;
    public:
        string what();
};