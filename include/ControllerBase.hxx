#ifndef _CONTROLLERBASE_H_
#define _CONTROLLERBASE_H_

#include "GameState.hxx"
#include "Widget.hxx"
#include <SDL/SDL.h>

class ControllerBase {
	protected:
		GameState* info;
		Widget* widget;

	public:
		ControllerBase();
		~ControllerBase();

		virtual int GetX();
		virtual int GetY();

		void RegisterGameState(GameState* info);
		void RegisterWidget(Widget* Widget);
};

#endif
