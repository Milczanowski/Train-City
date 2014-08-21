#pragma once
#include "stdafx.h"
#include "SDL.h"
#include <stdio.h>
#include "Time.h"
#include "Interface.h"

int main(int argc, char* argv[])
{
	try
	{
		Textures::initialize();
		Time _time;
		SDL_Event _event;
		SDL_PollEvent(&_event);
		Map map(GameObject(Vector2(200, 0), Vector2(800, 800), 0, Textures::getTexture("map.png")), "Resources/cities.txt");
		Interface _interface(GameObject( Vector2(0,20), Vector2(200,760),0, Textures::getTexture("interface.png")), &map);

		MapElement::_interface = &_interface;

		while (_event.type != SDL_QUIT)
		{
			GameObject::setEvent(_event);
			map.update();
			_interface.update();
			_time.update();
			GraphicDevice::begin();
			{
				map.draw();
				_interface.draw();
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