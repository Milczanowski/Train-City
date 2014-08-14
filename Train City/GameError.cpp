#include "StdAfx.h"
#include "GameError.h"



GameError::GameError(const std::string information):information(information)
{
}

GameError::GameError(const std::string information, const std::string sdl_error):information(information), sdl_error(sdl_error)
{
}

const char* GameError::what()const
{
	return information.c_str();
}

GameError::~GameError(void)
{
}

void GameError::generateErrorLog(const std::string filename)
{
	std::ofstream file(filename, std::ios::app);
	if(file.is_open())
	{
		file<<information<<sdl_error<<std::endl;
		file.close();
	}
	else throw GameError("Could not open file :"+filename);
}