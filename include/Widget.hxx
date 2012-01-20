#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <list>
using namespace std;

class Widget {
	protected:
		int pos_x, pos_y;
		int vel_x, vel_y;
		int dim_w, dim_h;
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
		
		void SetPositionX(int x);
		void SetPositionY(int y);
		void SetVelocityX(int x);
		void SetVelocityY(int y);
		void SetDimensionW(int w);
		void SetDimensionH(int h);

		int GetPositionX();
		int GetPositionY();
		int GetVelocityX();
		int GetVelocityY();
		int GetDimensionW();
		int GetDimensionH();

		void AddCollision(Widget*);
		void DelCollision(Widget*);
};

#endif
// vim: ts=2
