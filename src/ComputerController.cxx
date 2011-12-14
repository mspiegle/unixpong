#include "ComputerController.hxx"
#include "Common.hxx"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <stdio.h>
#include <math.h>

using namespace std;

ComputerController::ComputerController() {
}

ComputerController::~ComputerController() {
}

int ComputerController::GetY() {
	list<Widget*> balls = this->info->getBalls();
	list<Widget*>::const_iterator iter;
	Widget* curWidget = NULL;
	int curDist = -1;
	int dist = 0;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int y = 0;

	//find closest ball and home in on it
	for ( iter = balls.begin(); iter != balls.end(); iter++ ) {
		x2 = (*iter)->GetPositionX();
		x1 = this->widget->GetPositionX();
		y2 = (*iter)->GetPositionY();
		y1 = this->widget->GetPositionY();
		dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

		if ( curDist == -1 ) {
			curDist = dist;
			curWidget = (*iter);
		} else {
			if ( dist < curDist ) {
				curDist = dist;
				curWidget = (*iter);
			}
		}
	}

	y = curWidget->GetPositionY();

	if( (y - this->widget->GetDimensionH() / 2) < 0 )
		y = 0;
	else
		y = y - this->widget->GetDimensionH() / 2;

	return y;
}

// vim: ts=2
