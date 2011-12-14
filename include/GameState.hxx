#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "Widget.hxx"
#include <list>

using namespace std;

class GameState {
	private:
		list<Widget*> paddles;
		list<Widget*> balls;
		list<int> clients;

	public:
		GameState();
		~GameState();

		list<Widget*> getPaddles();
		list<Widget*> getBalls();
		list<int> getClients();

		void addPaddle(Widget* paddle);
		void addBall(Widget* ball);
		void addClient(int client);
};

#endif
// vim: ts=2
