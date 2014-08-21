#pragma once
#include "FunctionsAndDefinitions.h"
#include <iostream>
#include <fstream>
#include <string>

class GameError
{
private:
	std::string information, sdl_error;
public:
	GameError(const std::string);
	GameError(const std::string, const std::string);
	~GameError(void);
	const char* what()const throw();
	void generateErrorLog(const std::string );	
};

