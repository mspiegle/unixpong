#ifndef _LOCALCONTROLLER_H_
#define _LOCALCONTROLLER_H_

#include "ControllerBase.hxx"
#include <SDL/SDL.h>

class LocalController : public ControllerBase {
	private:
		SDL_Event event;

	public:
		LocalController();
		~LocalController();

		//void BindSource( SDL_Event &event );
		virtual int GetY();

};

#endif
