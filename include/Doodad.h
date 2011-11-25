#ifndef _DOODAD_H_
#define _DOODAD_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <list>
using namespace std;

class Doodad {
	protected:
		int xPos, yPos;
		int xVel, yVel;
		int wDim, hDim;
		list<Doodad*> colliders;
		bool ChkCollision(Doodad*);

	public:
		Doodad();
		~Doodad();

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

		void AddCollision(Doodad*);
		void DelCollision(Doodad*);
};

#endif
