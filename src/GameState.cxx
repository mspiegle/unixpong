#include "GameState.hxx"
#include <list>

GameState::GameState() {
}

GameState::~GameState() {
}

list<Widget*> GameState::getPaddles() {
	return this->paddles;
}

list<Widget*> GameState::getBalls() {
	return this->balls;
}

list<int> GameState::getClients() {
	return this->clients;
}

void GameState::addPaddle(Widget* paddle) {
	this->paddles.push_back(paddle);
}

void GameState::addBall(Widget* ball) {
	this->balls.push_back(ball);
}

void GameState::addClient(int client) {
	this->clients.push_back(client);
}
