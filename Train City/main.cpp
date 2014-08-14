#pragma once
#include "stdafx.h"
#include "SDL.h"
#include <stdio.h>
#include "GraphicDevice.h"
#include "Textures.h"
#include "Map.h"
#include "Time.h"

int main(int argc, char* argv[])
{
	try
	{
		Textures::initialize();

		Time _time;
		SDL_Event _event;
		SDL_PollEvent(&_event);
		Map map(GameObject(Vector2(200, 0), Vector2(800, 800), 0, Textures::getTexture("map.png")), "Resources/cities.txt");


		while (_event.type != SDL_QUIT)
		{

			GameObject::setEvent(_event);

			map.update();
			_time.update();
			GraphicDevice::begin();
			{
				map.draw();
				_time.draw(GraphicDevice::getColor(255, 255, 255, 255), Vector2(0, 0), 16);
			}
			GraphicDevice::end();
			SDL_PollEvent(&_event);
		}
	}
	catch (GameError & gameError)
	{
		gameError.generateErrorLog(errorFile);
	}

    return 0;
}