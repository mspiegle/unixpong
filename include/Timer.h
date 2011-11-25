#ifndef _TIMER_H_
#define _TIMER_H_

class Timer {
	private:
		int startTicks;
		int pausedTicks;

		bool running;
		bool paused;

	public:
		Timer();
		void Start();
		void Stop();
		void Pause();
		void Resume();

		int getTicks();

		bool isRunning();
		bool isPaused();
};

#endif
