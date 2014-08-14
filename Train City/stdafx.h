// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <sstream>

#define DEFAULT_POS_X 100
#define DEFAULT_POS_Y 100
#define DEFAULT_SIZE_W 1000
#define DEFAULT_SIZE_H 600
static const std::string errorFile = "ErrorLog.txt";
static const std::string DEFAULT_WIN_NAME = "Train City";
static const std::string windowSettings = "WindowSettings.txt";
static const std::string resourcesPath = "Resources/";
static const std::string texturesPath = "images/";
static const std::string fontName = "arial.ttf";
static const std::string iconFile = "icon.png";


const std::string intToString(const int value);

// TODO: reference additional headers your program requires here
