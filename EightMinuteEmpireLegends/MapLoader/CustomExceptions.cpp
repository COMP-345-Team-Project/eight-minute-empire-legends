#pragma once
#include "CustomExceptions.h"

InvalidFileFormatException::InvalidFileFormatException() {}

string InvalidFileFormatException::what() {
	return what_message;
}
