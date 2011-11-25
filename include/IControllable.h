#ifndef _ICONTROLLABLE_H_
#define _ICONTROLLABLE_H_

#include <ControllerBase.h>
#include <SDL.h>

class IControllable {
	public:
		virtual void HandleInput() = 0;
		virtual void RegisterController(ControllerBase* controller) = 0;
};

#endif
