#include "Widget.hxx"
#include "Common.hxx"
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <list>
#include <stdio.h>

using namespace std;

Widget::Widget() {
	this->pos_x = 0;
	this->pos_y = 0;
	this->vel_x = 0;
	this->vel_y = 0;
	this->dim_w = 0;
	this->dim_h = 0;
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
	return this->pos_x;
}

int Widget::GetPositionY() {
	return this->pos_y;
}

void Widget::Move() {
	HandleInput();

	this->pos_x += this->vel_x;

	if ( ( this->pos_x < 0 ) || ( this->pos_x + this->dim_w > SCREEN_WIDTH ) )
		this->pos_x -= this->vel_x;

	this->pos_y += this->vel_y;

	if ( ( this->pos_y < 0 ) || ( this->pos_y + this->dim_h > SCREEN_HEIGHT ) )
		this->pos_y -= this->vel_y;
}

int Widget::GetTopEdge() {
	return this->pos_y;
}

int Widget::GetRightEdge() {
	return this->pos_x + this->dim_w;
}

int Widget::GetLeftEdge() {
	return this->pos_x;
}

int Widget::GetBottomEdge() {
	return this->pos_y + this->dim_h;
}

void Widget::HandleInput() {
}

void Widget::Show() {
}

void Widget::SetPositionX(int x) {
	this->pos_x = x;
}

void Widget::SetPositionY(int y) {
	this->pos_y = y;
}

void Widget::SetVelocityX(int x) {
	this->vel_x = x;
}

void Widget::SetVelocityY(int y) {
	this->vel_y = y;
}

int Widget::GetDimensionW() {
	return this->dim_w;
}

int Widget::GetDimensionH() {
	return this->dim_h;
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
