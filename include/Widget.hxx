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
		list<Widget*> neighbors;
		void HandleInput();

	public:
		Widget();
		~Widget();

		virtual void Move();
		virtual void Draw();
	
		virtual int GetRightEdge();
		virtual int GetLeftEdge();
		virtual int GetTopEdge();
		virtual int GetBottomEdge();
	
		void SetDimensionW(int);
		void SetDimensionH(int);

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

		void AddNeighbor(Widget*);
		void DelNeighbor(Widget*);
		bool HitNeighbor(Widget*);
		list<Widget*> GetNeighbors();
};

#endif
// vim: ts=2
