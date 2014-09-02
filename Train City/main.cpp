#pragma once
#include "stdafx.h"
#include "SDL.h"
#include <stdio.h>
#include "Time.h"
#include "Interface.h"

enum MenuState
{
	menu,
	play,
	gameExit
};

class Container
{
public:
	MenuState menuState;
	Map *map;
	Time *time;

	Container():map(NULL),time(NULL), menuState(menu){}

	~Container()
	{
		delete map;
		delete time;
	}
};

Container container;
Interface * _interface;

void start()
{
		container.map = new Map(GameObject(Vector2(200, 0), Vector2(800, 800), 0, Textures::getTexture("map.png")), "Resources/cities.txt");
		_interface->setMapPionter(container.map);
		container.time = new Time();
		MapElement::_interface = _interface;
		container.menuState=play;
}

void exit()
{
	container.menuState=gameExit;
}



int main(int argc, char* argv[])
{
	try
	{
		Textures::initialize();
		SDL_Event _event; 
		SDL_PollEvent(&_event);
		_interface =new Interface(GameObject( Vector2(0,20), Vector2(200,760),0, Textures::getTexture("interface.png")));

		_interface->addButton(Textures::getTexture("errorImage"),"Start",&start);
		_interface->addButton(Textures::getTexture("errorImage"),"Exit",&exit);


		while(container.menuState!=gameExit && _event.type !=SDL_QUIT)
		{
			GameObject::setEvent(_event);
			switch(container.menuState)
			{
			case menu:
				{
					_interface->update();
					GraphicDevice::begin();
					{
						_interface->draw();
					}
					GraphicDevice::end();

				}break;
			case play:
				  {
						container.map->update();
						_interface->update();
						container.time->update();

						GraphicDevice::begin();
						{
							container.map->draw();
							Player::getInstance().drawCash(Vector2(100,0),16);
							_interface->draw();
							container.time->draw(GraphicDevice::getColor(255, 255, 255, 255), Vector2(0, 0), 16);
							Player::getInstance().drawTrains();
						}
						GraphicDevice::end();
				  }break;
			}
			SDL_PollEvent(&_event);
		}
	}
	catch (GameError & gameError)
	{
		gameError.generateErrorLog(errorFile);
	}
	

	delete _interface;

    return 0;
}

