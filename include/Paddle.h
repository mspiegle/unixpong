#ifndef _PADDLE_H_
#define _PADDLE_H_

#include <Doodad.h>
#include <IControllable.h>
#include <ControllerBase.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class Paddle : public Doodad, public IControllable {
	private:
		ControllerBase* controller;

	public:
		Paddle();
		~Paddle();

		void Show();

		//IControllable Interface
		void HandleInput();
		void RegisterController(ControllerBase* controller);
};

#endif
