#include <ControllerBase.h>
#include <GameState.h>
#include <Common.h>

ControllerBase::ControllerBase() {
}

ControllerBase::~ControllerBase() {
}

int ControllerBase::GetX() {
	return 0;
}

int ControllerBase::GetY() {
	return 0;
}

void ControllerBase::RegisterGameState(GameState* info) {
	this->info = info;
}

void ControllerBase::RegisterDoodad(Doodad* doodad) {
	this->doodad = doodad;
}
