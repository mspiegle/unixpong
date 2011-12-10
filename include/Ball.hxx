#ifndef _BALL_H_
#define _BALL_H_

#include "Doodad.hxx"
#include "IControllable.hxx"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class Ball : public Doodad {
	public:
		Ball();
		~Ball();

		void Show();
		void Move();
		int GetLeftEdge();
		int GetRightEdge();
		int GetTopEdge();
		int GetBottomEdge();

};

#endif
