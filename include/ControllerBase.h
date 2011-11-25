#ifndef _CONTROLLERBASE_H_
#define _CONTROLLERBASE_H_

#include <SDL.h>
#include <GameState.h>
#include <Doodad.h>

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
