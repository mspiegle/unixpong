#ifndef _CONTROLLERBASE_H_
#define _CONTROLLERBASE_H_

#include "GameState.hxx"
#include "Doodad.hxx"
#include <SDL/SDL.h>

class ControllerBase {
	protected:
		GameState* info;
		Doodad* doodad;

	public:
		ControllerBase();
		~ControllerBase();

		virtual int GetX();
		virtual int GetY();

		void RegisterGameState(GameState* info);
		void RegisterDoodad(Doodad* doodad);
};

#endif
