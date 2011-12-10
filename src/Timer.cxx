#include "Timer.hxx"
#include <SDL/SDL.h>

Timer::Timer() {
	this->startTicks = 0;
	this->pausedTicks = 0;
	this->paused = false;
	this->running = false;
}

void Timer::Start() {
	this->running = true;
	this->paused = false;
	this->startTicks = SDL_GetTicks();
}

void Timer::Stop() {
	this->running = false;
	this->paused = false;
}

void Timer::Pause() {
	if ( ( this->running == true ) && ( this->paused == false ) ) {
		this->paused = true;
		this->pausedTicks = SDL_GetTicks() - this->startTicks;
	}
}

void Timer::Resume() {
	if ( this->paused == true ) {
		this->paused = false;
		this->startTicks = SDL_GetTicks() - this->pausedTicks;
		this->pausedTicks = 0;
	}
}

int Timer::getTicks() {
	if ( this->running == true ) {
		if ( this->paused == true )
			return this->pausedTicks;
		else
			return SDL_GetTicks() - this->startTicks;
	}
	return 0;
}

bool Timer::isRunning() {
	return this->running;
}

bool Timer::isPaused() {
	return this->paused;
}
