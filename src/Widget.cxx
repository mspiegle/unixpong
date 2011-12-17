#include "Widget.hxx"
#include "Common.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <list>
#include <stdio.h>

using namespace std;

Widget::Widget() {
	this->xPos = 0;
	this->yPos = 0;
	this->xVel = 0;
	this->yVel = 0;
	this->wDim = 0;
	this->hDim = 0;
}

Widget::~Widget() {
}

bool Widget::ChkCollision(Widget* Widget) {
	int SourceLeft   = this->GetLeftEdge();
	int SourceRight  = this->GetRightEdge();
	int SourceTop    = this->GetTopEdge();
	int SourceBottom = this->GetBottomEdge();

	int TargetLeft   = Widget->GetLeftEdge();
	int TargetRight  = Widget->GetRightEdge();
	int TargetTop    = Widget->GetTopEdge();
	int TargetBottom = Widget->GetBottomEdge();

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

int Widget::GetPositionX() {
	return this->xPos;
}

int Widget::GetPositionY() {
	return this->yPos;
}

void Widget::Move() {
	HandleInput();

	this->xPos += this->xVel;

	if ( ( this->xPos < 0 ) || ( this->xPos + this->wDim > SCREEN_WIDTH ) )
		this->xPos -= this->xVel;

	this->yPos += this->yVel;

	if ( ( this->yPos < 0 ) || ( this->yPos + this->hDim > SCREEN_HEIGHT ) )
		this->yPos -= this->yVel;
}

int Widget::GetTopEdge() {
	return this->yPos;
}

int Widget::GetRightEdge() {
	return this->xPos + this->wDim;
}

int Widget::GetLeftEdge() {
	return this->xPos;
}

int Widget::GetBottomEdge() {
	return this->yPos + this->hDim;
}

void Widget::HandleInput() {
}

void Widget::Show() {
}

void Widget::SetPositionX(int x) {
	this->xPos = x;
}

void Widget::SetPositionY(int y) {
	this->yPos = y;
}

void Widget::SetVelocityX(int x) {
	this->xVel = x;
}

void Widget::SetVelocityY(int y) {
	this->yVel = y;
}

int Widget::GetDimensionW() {
	return this->wDim;
}

int Widget::GetDimensionH() {
	return this->hDim;
}

void Widget::AddCollision(Widget* Widget) {
	colliders.push_back(Widget);
}

void Widget::DelCollision(Widget* Widget) {
	colliders.remove(Widget);
}

bool ChkCollision() {
	return false;
}

// vim: ts=2
