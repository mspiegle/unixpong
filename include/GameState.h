#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include <Doodad.h>

using namespace std;

//class Doodad;

class GameState {
	private:
		list<Doodad*> paddles;
		list<Doodad*> balls;
		list<int> clients;

	public:
		GameState();
		~GameState();

		list<Doodad*> getPaddles();
		list<Doodad*> getBalls();
		list<int> getClients();

		void addPaddle(Doodad* paddle);
		void addBall(Doodad* ball);
		void addClient(int client);
};

#endif
