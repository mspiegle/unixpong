#include "LocalController.hxx"
#include "Common.hxx"

LocalController::LocalController() {
}

LocalController::~LocalController() {
}

int LocalController::GetY() {
	int y = -1;
	SDL_GetMouseState(NULL, &y);
	if ((y > 0) && (y < (SCREEN_HEIGHT - this->widget->GetDimensionH()))) {
		return y;
	}
	return -1;
}
// vim: ts=2
