#include "Ball.hxx"
#include "Common.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <math.h>

Ball::Ball() {
	SetPositionX(0);
	SetPositionY(0);
	SetVelocityX(0);
	SetVelocityY(0);
	SetDimensionW(20);
	SetDimensionH(20);
}

Ball::~Ball() {
}

void Ball::Move() {
	list<Widget*>::const_iterator iter;
	for(iter = GetNeighbors().begin(); iter != GetNeighbors().end(); iter++) {
		if(HitNeighbor(*iter)) {
			//change ball direction
			SetVelocityX(GetVelocityX() * -1);

			//calculate "spin"
			int center = ((*iter)->GetPositionY() + ((*iter)->GetDimensionH() / 2));
			if (this->GetPositionY() > center) {
				SetVelocityY(abs(GetVelocityY()));
			} else {
				SetVelocityY(abs(GetVelocityY()) * -1);
			}
		}
	}

	SetPositionX(GetPositionX() + GetVelocityX());

	if ((GetPositionX() < 0)
	    || (GetPositionX() + GetDimensionW() > SCREEN_WIDTH)) {
		SetPositionX(GetPositionX() - GetVelocityX());
	}

	SetPositionY(GetPositionY() - GetVelocityY());

	if ((GetPositionY() < 0)
	    || (GetPositionY() + GetDimensionH() > SCREEN_HEIGHT)) {
		SetPositionY(GetPositionY() - GetVelocityY());
	}
}

int Ball::GetTopEdge() {
	return GetPositionY() - (GetDimensionH() / 2);
}

int Ball::GetRightEdge() {
	return GetPositionX() + (GetDimensionW() / 2);
}

int Ball::GetBottomEdge() {
	return GetPositionY() + (GetDimensionH() / 2);
}

int Ball::GetLeftEdge() {
	return GetPositionX() - (GetDimensionW() / 2);
}

void Ball::Draw() {
	glTranslatef(GetPositionX(), GetPositionY(), 0);

	int temp;
	glBegin (GL_LINE_LOOP);
		for (temp = 0; temp < 360; temp++) {
			//convert degrees to radians
			float deg_in_rad = temp * (3.14159 / 180);
			glVertex2f(cos(deg_in_rad) * (GetDimensionW() / 2),
			           sin(deg_in_rad) * (GetDimensionH() / 2));
		}
	glEnd();
	glLoadIdentity();
}
// vim: ts=2
