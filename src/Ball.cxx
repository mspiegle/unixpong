#include "Ball.hxx"
#include "Common.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <math.h>

Ball::Ball() {
	this->pos_x = 0;
	this->pos_y = 0;
	this->vel_x = 0;
	this->vel_y = 0;
	this->dim_w = 20;
	this->dim_h = 20;
}

Ball::~Ball() {
}

void Ball::Move() {
	list<Widget*>::const_iterator iter;
for( iter = colliders.begin(); iter != colliders.end(); iter++ ) {
if( ChkCollision(*iter) ) {
//change ball direction
this->xVel *= -1;
//calculate "spin"
int center = ((*iter)->GetPositionY() + ((*iter)->GetDimensionH() / 2));
if ( this->yPos > center )
this->yVel = abs(this->yVel);
else
this->yVel = abs(this->yVel) * -1;
}
}

this->xPos += this->xVel;

if ( ( this->xPos < 0 ) || ( this->xPos + this->wDim > SCREEN_WIDTH ) )
this->xPos -= this->xVel;

this->yPos += this->yVel;

if ( ( this->yPos < 0 ) || ( this->yPos + this->hDim > SCREEN_HEIGHT ) )
this->yPos -= this->yVel;
}

int Ball::GetTopEdge() {
	return this->yPos - (this->hDim / 2);
}

int Ball::GetRightEdge() {
	return this->xPos + (this->wDim / 2);
}

int Ball::GetBottomEdge() {
	return this->yPos + (this->hDim / 2);
}

int Ball::GetLeftEdge() {
	return this->xPos - (this->wDim / 2);
}

void Ball::Show() {
	glTranslatef( this->xPos, this->yPos, 0 );

	int temp;
	const float DEG2RAD = 3.14159 / 180;
	glBegin ( GL_LINE_LOOP );
		for ( temp = 0; temp < 360; temp++ ) {
			float degInRad = temp * DEG2RAD;
			glVertex2f( cos(degInRad) * (this->wDim / 2), sin(degInRad) * (this->hDim / 2) );
		}
	glEnd();
	glLoadIdentity();
}
// vim: ts=2 sw=1
