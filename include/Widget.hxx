#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <list>
using namespace std;

class Widget {
	protected:
		int xPos, yPos;
		int xVel, yVel;
		int wDim, hDim;
		list<Widget*> colliders;
		bool ChkCollision(Widget*);

	public:
		Widget();
		~Widget();

		virtual void Move();
		virtual void Show();
		virtual void HandleInput();
	
		virtual int GetRightEdge();
		virtual int GetLeftEdge();
		virtual int GetTopEdge();
		virtual int GetBottomEdge();
		
		int GetDimensionW();
		int GetDimensionH();
		
		void SetPositionX(int x);
		void SetPositionY(int y);
		void SetVelocityX(int x);
		void SetVelocityY(int y);

		int GetPositionX();
		int GetPositionY();
		int GetVelocityX();
		int GetVelocityY();

		void AddCollision(Widget*);
		void DelCollision(Widget*);
};

#endif
// vim: ts=2
