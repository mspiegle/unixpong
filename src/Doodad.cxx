#include "Doodad.hxx"
#include "Common.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <list>
#include <stdio.h>

using namespace std;

Doodad::Doodad() {
	this->xPos = 0;
	this->yPos = 0;
	this->xVel = 0;
	this->yVel = 0;
	this->wDim = 0;
	this->hDim = 0;
}

Doodad::~Doodad() {
}

bool Doodad::ChkCollision(Doodad* doodad) {
	int SourceLeft   = this->GetLeftEdge();
	int SourceRight  = this->GetRightEdge();
	int SourceTop    = this->GetTopEdge();
	int SourceBottom = this->GetBottomEdge();

	int TargetLeft   = doodad->GetLeftEdge();
	int TargetRight  = doodad->GetRightEdge();
	int TargetTop    = doodad->GetTopEdge();
	int TargetBottom = doodad->GetBottomEdge();

	//Lets bounce all the easy non-collision possibilities first
    if ( SourceBottom < TargetTop )
        return false;

    if ( SourceTop > TargetBottom )
        return false;

    if ( SourceLeft > TargetRight )
        return false;

    if ( SourceRight < TargetLeft )
        return false;

	return true;
}

int Doodad::GetPositionX() {
	return this->xPos;
}

int Doodad::GetPositionY() {
	return this->yPos;
}

void Doodad::Move() {
	HandleInput();

	this->xPos += this->xVel;

	if ( ( this->xPos < 0 ) || ( this->xPos + this->wDim > SCREEN_WIDTH ) )
		this->xPos -= this->xVel;

	this->yPos += this->yVel;

	if ( ( this->yPos < 0 ) || ( this->yPos + this->hDim > SCREEN_HEIGHT ) )
		this->yPos -= this->yVel;
}

int Doodad::GetTopEdge() {
	return this->yPos;
}

int Doodad::GetRightEdge() {
	return this->xPos + this->wDim;
}

int Doodad::GetLeftEdge() {
	return this->xPos;
}

int Doodad::GetBottomEdge() {
	return this->yPos + this->hDim;
}

void Doodad::HandleInput() {
}

void Doodad::Show() {
}

void Doodad::SetPositionX(int x) {
	this->xPos = x;
}

void Doodad::SetPositionY(int y) {
	this->yPos = y;
}

void Doodad::SetVelocityX(int x) {
	this->xVel = x;
}

void Doodad::SetVelocityY(int y) {
	this->yVel = y;
}

int Doodad::GetDimensionW() {
	return this->wDim;
}

int Doodad::GetDimensionH() {
	return this->hDim;
}

void Doodad::AddCollision(Doodad* doodad) {
	colliders.push_back(doodad);
}

void Doodad::DelCollision(Doodad* doodad) {
	colliders.remove(doodad);
}

bool ChkCollision() {
	return false;
}
