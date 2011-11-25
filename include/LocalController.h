#ifndef _LOCALCONTROLLER_H_
#define _LOCALCONTROLLER_H_

#include <ControllerBase.h>
#include <SDL.h>

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
