#include "Common.hxx"
#include "Paddle.hxx"
#include "Ball.hxx"
#include "Timer.hxx"
#include "LocalController.hxx"
#include "ComputerController.hxx"
#include "GameState.hxx"
#include "Connection.hxx"
#include <list>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>


bool        opt_RunServer = false;
bool        opt_RunClient = false;
bool        opt_Help      = false;
char const* opt_Hostname  = "0.0.0.0";
int         opt_Port      = 50525;
char const* Options       = "hsc:p:";
char const* HelpText      = "Usage: %s [-s] | [-c hostname] [-p port]\n";

char *CheckOptions(int argc, char** argv) {
	int o;
	char* error;
	struct hostent* he;

	while ( -1 != (o = getopt(argc, argv, Options)) ) {
		switch(o) {
			case 's': opt_RunServer = true;           break;
			case 'c': opt_RunClient = true;
			          opt_Hostname  = strdup(optarg); break;
			case 'p': opt_Port      = atoi(optarg);   break;
			case 'h': opt_Help      = true;           break;
			default:  error         = strdup("Invalid Argument!\n"); return error;
		}
	}

	if ( opt_RunClient && argc < 3 ) {
		error = strdup("Clients need to specify a server to connect to\n");
		return error;
	}

	if ( opt_RunClient && opt_RunServer ) {
		error = strdup("You can't run the server and client at the same time\n");
		return error;
	}

	if ( NULL == (he = gethostbyname(opt_Hostname)) ) {
		error = strdup("Error resolving hostname\n");
		return error;
	} else {
		if ( he->h_addr_list[0] != NULL ) {
			opt_Hostname = inet_ntoa(*(struct in_addr*)(he->h_addr_list[0]));
		} else {
			error = strdup("Error setting hostname\n");
			return error;
		}
	}

	//success
	return 0;
}


int main(int argc, char** argv) {

	char* error;

	//check for commandline options
	if (0 != (error = CheckOptions(argc, argv)) || opt_Help) {
		if (!opt_Help) {
			printf("There was an error in your arguments:\n");
			printf("%s\n", error);		
		}
		printf("%s\n", HelpText);
		return EXIT_FAILURE;
	}

	if (opt_RunServer) {
		UdpConnection cxn;
		if (!cxn.Socket()) {
			printf("Error building socket\n");
			return EXIT_FAILURE;
		}
		if (!cxn.Bind(opt_Port)) {
			printf("Error binding port\n");
			return EXIT_FAILURE;
		}
	}

	if (opt_RunClient) {
		UdpConnection cxn;
        if (!cxn.Socket()) {
            printf("Error building socket\n");
            return EXIT_FAILURE;
        }
		if (!cxn.Connect(opt_Hostname, opt_Port)) {
			printf("Error connecting to server\n");
			return EXIT_FAILURE;
		}
	}

	//SDL/GL Init
	if (-1 == SDL_Init(SDL_INIT_EVERYTHING)) {
		printf("Init() Failure\n");
		return EXIT_FAILURE;
	}
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	if (NULL == SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
	                             SCREEN_BPP, SDL_OPENGL)) {
		printf("SetVideoMode() Failed\n");
		return EXIT_FAILURE;
	}
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(GL_NO_ERROR != glGetError()) {
		printf("OpenGL Error\n");
		return EXIT_FAILURE;
	}
	SDL_WM_SetCaption("Unix Pong!", NULL);

	//support stuff
	Timer fps;
	SDL_Event event;
	bool isRunning = true;
	list<Doodad *> doodads;
	list<Doodad *>::const_iterator doodadIter;

	//paddle-specific stuff
	Paddle *leftPaddle = new Paddle();
	leftPaddle->SetPositionX(10);
	leftPaddle->SetPositionY(50);
	doodads.push_back(leftPaddle);
	Paddle *rightPaddle = new Paddle();
	rightPaddle->SetPositionX(SCREEN_WIDTH - (10 + rightPaddle->GetDimensionW()));
	rightPaddle->SetPositionY(50);
	doodads.push_back(rightPaddle);

	//ball-specific stuff
	Ball *ball1 = new Ball();
	ball1->SetPositionX(SCREEN_WIDTH / 2);
	ball1->SetPositionY(SCREEN_HEIGHT / 2);
	ball1->SetVelocityX(-10);
	ball1->SetVelocityY(1);
	ball1->AddCollision(leftPaddle);
	ball1->AddCollision(rightPaddle);
	Ball *ball2 = new Ball();
	ball2->SetPositionX(SCREEN_WIDTH / 2);
	ball2->SetPositionY(SCREEN_HEIGHT / 2);
	ball2->SetVelocityX(4);
	ball2->SetVelocityY(-1);
	ball2->AddCollision(leftPaddle);
	ball2->AddCollision(rightPaddle);
	doodads.push_back(ball1);
	doodads.push_back(ball2);
	
	//game state object
	GameState *info = new GameState();
	info->addPaddle(leftPaddle);
	info->addPaddle(rightPaddle);
	info->addBall(ball1);
	info->addBall(ball2);

	//controllers
	LocalController *human = new LocalController();
	human->RegisterGameState(info);
	human->RegisterDoodad(rightPaddle);
	rightPaddle->RegisterController(human);
	ComputerController *computer = new ComputerController();
	computer->RegisterGameState(info);
	computer->RegisterDoodad(leftPaddle);
	leftPaddle->RegisterController(computer);

	while ( isRunning == true ) {
		fps.Start();
	
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isRunning = false;

			if (event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
		}

		for(doodadIter = doodads.begin();
		    doodadIter != doodads.end();
		    doodadIter++ ) {
			(*doodadIter)->Move();
		}

		glClear(GL_COLOR_BUFFER_BIT);
	
		for(doodadIter = doodads.begin();
		    doodadIter != doodads.end();
		    doodadIter++ ) {
			(*doodadIter)->Show();
		}

		SDL_GL_SwapBuffers();

		if (fps.getTicks() < 1000 / FPS) {
			SDL_Delay( (1000 / FPS) - fps.getTicks() );
		}
	}

	delete(human);
	delete(computer);
	delete(leftPaddle);
	delete(rightPaddle);
	delete(ball1);
	delete(ball2);
	delete(info);

	SDL_Quit();
	return EXIT_SUCCESS;
}

// vim: ts=2
