#include "GameState.hxx"
#include <list>

GameState::GameState() {
}

GameState::~GameState() {
}

list<Doodad*> GameState::getPaddles() {
	return this->paddles;
}

list<Doodad*> GameState::getBalls() {
	return this->balls;
}

list<int> GameState::getClients() {
	return this->clients;
}

void GameState::addPaddle(Doodad* paddle) {
	this->paddles.push_back(paddle);
}

void GameState::addBall(Doodad* ball) {
	this->balls.push_back(ball);
}

void GameState::addClient(int client) {
	this->clients.push_back(client);
}
