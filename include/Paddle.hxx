#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "Widget.hxx"
#include "IControllable.hxx"
#include "ControllerBase.hxx"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class Paddle : public Widget, public IControllable {
	private:
		ControllerBase* controller;

	public:
		Paddle();
		~Paddle();

		void Draw();

		//IControllable Interface
		void HandleInput();
		void RegisterController(ControllerBase* controller);
};

#endif
