#include "stdafx.h"
#include "SDL.h"
#include <stdio.h>
#include "GraphicDevice.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Textures.h"

int main(int argc, char* argv[])
{
	Textures::initialize();

	SDL_Event _event;
	SDL_PollEvent(&_event);

	while(_event.type!=SDL_QUIT)
	{
		GameObject::setEvent(_event);

		//mainMap.update();
		GraphicDevice::begin();
		{
		//	mainMap.draw();

		}
		GraphicDevice::end();
		SDL_PollEvent(&_event);
	}
    return 0;
}