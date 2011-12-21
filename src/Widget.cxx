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

void Widget::Move() {
	//TODO: this could be way more advanced
	//take the current velocity, and add it to the positions
	this->pos_x += this->vel_x;

	if ((this->pos_x < 0) || (this->pos_x + this->dim_w > SCREEN_WIDTH)) {
		this->pos_x -= this->vel_x;
	}

	this->pos_y += this->vel_y;

	if ((this->pos_y < 0) || (this->pos_y + this->dim_h > SCREEN_HEIGHT)) {
		this->pos_y -= this->vel_y;
	}
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

void Widget::Draw() {
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

int Widget::GetPositionX() {
	return this->pos_x;
}

int Widget::GetPositionY() {
	return this->pos_y;
}

int Widget::GetVelocityX() {
	return this->pos_x;
}

int Widget::GetVelocityY() {
	return this->pos_y;
}

void Widget::SetDimensionW(int w) {
	this->dim_w = w;
}

void Widget::SetDimensionH(int h) {
	this->dim_h = h;
}

int Widget::GetDimensionW() {
	return this->dim_w;
}

int Widget::GetDimensionH() {
	return this->dim_h;
}

void Widget::AddNeighbor(Widget* Widget) {
	neighbors.push_back(Widget);
}

void Widget::DelNeighbor(Widget* Widget) {
	neighbors.remove(Widget);
}

bool Widget::HitNeighbor(Widget* Widget) {
	//TODO: More advanced collision detection based on SAT
	//Lets bounce all the easy non-collision possibilities first
	if (this->GetBottomEdge() < Widget->GetTopEdge()) {
		return false;
	}

	if (this->GetTopEdge() > Widget->GetBottomEdge()) {
		return false;
	}

	if (this->GetLeftEdge() > Widget->GetRightEdge()) {
		return false;
	}

	if (this->GetRightEdge() < Widget->GetLeftEdge()) {
		return false;
	}

	return true;
}

list<Widget*> Widget::GetNeighbors() {
	return this->neighbors;
}


// vim: ts=2
