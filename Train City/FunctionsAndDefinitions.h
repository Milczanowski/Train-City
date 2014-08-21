#pragma once
#include <string>
#include <string.h>
#include <sstream>
#include <tchar.h>
#include <iomanip>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include "Vector2.h"


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

const Vector2 cityInfoSize(300, 150);
const Vector2 basicInfoSize(100, 20);



template <typename T>
inline const std::string ToString(const T value)
{
	std::ostringstream text;
	text << value;
	return text.str();
}

template<>
inline const std::string ToString<float>(const float value)
{
	char buffer[32];
	sprintf_s(buffer, 32, "%0.2f", value);
	return buffer;
}


