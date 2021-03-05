// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <exception>
#include <fstream>

// JSON parsing for map loader
#include "../Vendor/nlohmann/json.hpp"

// Argument parsing for Driver
// http://tclap.sourceforge.net/
#include "../Vendor/tclap/Arg.h"
#include "../Vendor/tclap/CmdLine.h"

#endif //PCH_H