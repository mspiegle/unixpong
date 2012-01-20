#include "Common.hxx"
#include "ControllerBase.hxx"
#include "IControllable.hxx"
#include "Paddle.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>

Paddle::Paddle() {
	SetPositionX(0);
	SetPositionY(0);
	SetVelocityX(0);
	SetVelocityY(0);
	SetDimensionW(20);
	SetDimensionH(150);
}

Paddle::~Paddle() {
}

void Paddle::HandleInput() {
	int y = -1;
	if ( -1 == (y = controller->GetY()) ) {
	} else {
		SetPositionY(y);
	}
}

void Paddle::RegisterController(ControllerBase* controller) {
	this->controller = controller;
}

void Paddle::Show() {
	glTranslatef(GetPositionX(), GetPositionY(), 0);

	glBegin(GL_QUADS);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex3f(0, 0, 0);
		glVertex3f(GetDimensionW(), 0, 0);
		glVertex3f(GetDimensionW(), GetDimensionH(), 0);
		glVertex3f(0, GetDimensionH(), 0);
	glEnd();

	glLoadIdentity();
}

// vim: ts=2
