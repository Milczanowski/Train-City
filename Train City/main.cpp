#pragma once
#include "stdafx.h"
#include "SDL.h"
#include <stdio.h>
#include "Time.h"
#include "Interface.h"
#include "GameOver.h"

enum MenuState
{
	menu,
	play,
	gameOver,
	gameExit
};

class Container
{
public:
	MenuState menuState;
	Map *map;
	Time *time;
	Interface * _interface;

	Container():map(NULL),time(NULL), menuState(menu), _interface(NULL){}

	~Container()
	{
		delete map;
		delete time;
		delete _interface;
	}
};

Container container;


void start()
{
	if(container.map==NULL)
		container.map = new Map(GameObject(Vector2(200, 0), Vector2(800, 800), 0, Textures::getTexture("map.png")), "Resources/cities.txt");
	if(container.time==NULL)
		container.time = new Time();
	if(container._interface==NULL)
		container._interface = new Interface(GameObject(Vector2(0,20),Vector2(200,760),0,Textures::getTexture("interface.png")),container.map);
		MapElement::_interface = container._interface;
		container.menuState= play;
}

void exit()
{
	container.menuState=gameExit;
}

void save()
{
	if(container.time!=NULL && container.map!=NULL)
	{
		std::ofstream saveFile(resourcesPath+saveGameFile);
		if(saveFile.is_open())
		{	
			saveFile<<*(container.time);
			saveFile<<*(container.map);
			saveFile<<Player::getInstance();


			saveFile.close();
		}
		else throw GameError("can not open file", resourcesPath+saveGameFile);
	}
}

void load()
{
	std::ifstream loadFile(resourcesPath+saveGameFile);
	if(loadFile.is_open())
	{
		start();
		loadFile>>*(container.time);
		loadFile>>*(container.map);
	}
}


int main(int argc, char* argv[])
{
	try
	{
		Textures::initialize();
		SDL_Event _event; 
		SDL_PollEvent(&_event);

		ButtonList buttonList;
		
		buttonList.push_back(Button( GameObject(Vector2(410,100),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Start", &start));
		buttonList.push_back(Button( GameObject(Vector2(410,210),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Save", &save));
		buttonList.push_back(Button( GameObject(Vector2(410,320),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Load", &load));
		buttonList.push_back(Button( GameObject(Vector2(410,430),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Exit", &exit));

		while(container.menuState!=gameExit && _event.type !=SDL_QUIT)
		{
			GameObject::setEvent(_event);
			switch(container.menuState)
			{
			case menu:
				{
					
					for(ButtonList::iterator iter  = buttonList.begin(); iter!=buttonList.end();iter++)
						iter->update();

					GraphicDevice::begin();
					{
						for(ButtonList::iterator iter  = buttonList.begin(); iter!=buttonList.end();iter++)
							iter->draw();
					}
					GraphicDevice::end();

				}break;
			case play:
				  {
						container.map->update();
						container._interface->update();
						container.time->update();
						try
						{
							Player::getInstance().updateTrains();
						}
						catch(GameOver &gameOver)
						{
							container.menuState = MenuState::gameOver;
						}
						GraphicDevice::begin();
						{
							container.map->draw();
							Player::getInstance().drawCash(Vector2(100,0),16);
							container._interface->draw();
							container.time->draw(GraphicDevice::getColor(255, 255, 255, 255), Vector2(0, 0), 16);
						}
						GraphicDevice::end();

						if(_event.key.keysym.sym == SDLK_ESCAPE)
							container.menuState = menu;
				  }break;
			case gameOver:
				{
					if(_event.type == SDL_KEYDOWN)
						container.menuState = menu;
					GraphicDevice::begin();
					GraphicDevice::drawTexture(Textures::getTexture("game_over.jpg"),Vector2(0,0),Vector2(1000,800));
					GraphicDevice::end();
				};
			}
			SDL_PollEvent(&_event);
		}
	}
	catch (GameError & gameError)
	{
		gameError.generateErrorLog(errorFile);
	}
	
    return 0;
}

