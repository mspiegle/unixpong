#ifndef _BALL_H_
#define _BALL_H_

#include "Widget.hxx"
#include "IControllable.hxx"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class Ball : public Widget {
	public:
		Ball();
		~Ball();

		void Draw();
		void Move();
		int GetLeftEdge();
		int GetRightEdge();
		int GetTopEdge();
		int GetBottomEdge();

		void HandleInput();

};

#endif
