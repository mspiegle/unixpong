#include "Common.hxx"
#include "ControllerBase.hxx"
#include "IControllable.hxx"
#include "Paddle.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>

Paddle::Paddle() {
	xPos = 0;
	yPos = 0;
	xVel = 0;
	yVel = 0;
	wDim = 20;
	hDim = 150;
}

Paddle::~Paddle() {
}

void Paddle::HandleInput() {
	int y = -1;
	if ( -1 == (y = controller->GetY()) ) {
	} else {
		this->yPos = y;
	}
}

void Paddle::RegisterController(ControllerBase* controller) {
	this->controller = controller;
}

void Paddle::Show() {
	glTranslatef( this->xPos, this->yPos, 0 );

	glBegin(GL_QUADS);
		glColor4f( 1.0, 1.0, 1.0, 1.0 );
		glVertex3f( 0, 0, 0 );
		glVertex3f( this->wDim, 0, 0 );
		glVertex3f( this->wDim, this->hDim, 0 );
		glVertex3f( 0, this->hDim, 0 );
	glEnd();

	glLoadIdentity();
}

// vim: ts=2
