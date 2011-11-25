#include <ComputerController.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <stdio.h>
#include <Common.h>
#include <math.h>

using namespace std;

ComputerController::ComputerController() {
}

ComputerController::~ComputerController() {
}

int ComputerController::GetY() {
	list<Doodad*> balls = this->info->getBalls();
	list<Doodad*>::const_iterator iter;
	Doodad* curDoodad = NULL;
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
		x1 = this->doodad->GetPositionX();
		y2 = (*iter)->GetPositionY();
		y1 = this->doodad->GetPositionY();
		dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

		if ( curDist == -1 ) {
			curDist = dist;
			curDoodad = (*iter);
		} else {
			if ( dist < curDist ) {
				curDist = dist;
				curDoodad = (*iter);
			}
		}
	}

	y = curDoodad->GetPositionY();

	if( (y - this->doodad->GetDimensionH() / 2) < 0 )
		y = 0;
	else
		y = y - this->doodad->GetDimensionH() / 2;

	return y;
}
