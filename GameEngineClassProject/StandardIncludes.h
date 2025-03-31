#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#define GLM_ENABLED_EXPERIMENTAL

#define SDL_MAIN_HANDLED

#define NATIVE_XRES 1920
#define NATIVE_YRES 1080

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cinttypes>
#include <stdio.h>
#include <thread>
#include <map>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>
#include <SDL_mixer.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> //to_string wasnt working without this

#include "Singleton.h"
#include "BasicStructs.h"

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) {OutputDebugStringA(_msg); std::abort(); }
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDire getcwd
#endif


using namespace std;

#endif