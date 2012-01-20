#include "Ball.hxx"
#include "Common.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <math.h>

Ball::Ball() {
	this->SetPositionX(0);
	this->SetPositionY(0);
	this->SetVelocityX(0);
	this->SetVelocityY(0);
	this->SetDimensionW(20);
	this->SetDimensionH(20);
}

Ball::~Ball() {
}

void Ball::Move() {
	list<Widget*>::const_iterator iter;
	for(iter = colliders.begin(); iter != colliders.end(); iter++) {
		if(ChkCollision(*iter)) {
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

	if ((GetPositionX() < 0) || 
	    (GetPositionX() + GetDimensionW() > SCREEN_WIDTH)) {
		SetPositionX(GetPositionX() - GetVelocityX());
	}

	SetPositionY(GetPositionY() + GetVelocityY());

	if ((GetPositionY() < 0) ||
	    (GetPositionY() + GetDimensionH() > SCREEN_HEIGHT)) {
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

void Ball::Show() {
	glTranslatef(GetPositionX(), GetPositionY(), 0 );

	int temp;
	const float DEG2RAD = 3.14159 / 180;
	glBegin (GL_LINE_LOOP);
		for ( temp = 0; temp < 360; temp++ ) {
			float degInRad = temp * DEG2RAD;
			glVertex2f(cos(degInRad) * (GetDimensionW() / 2),
			           sin(degInRad) * (GetDimensionH() / 2));
		}
	glEnd();
	glLoadIdentity();
}
// vim: ts=2
