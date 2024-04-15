#include "Timer.h"

Timer::Timer() {
	start_tick = 0;
	paused_tick = 0;

	is_paused = false;
	is_started = false;

}

Timer::~Timer() {}

void Timer::START() {
	is_started = true;
	is_paused = false;

	start_tick = SDL_GetTicks();
}

void Timer::STOP() {
	is_paused = false;
	is_started = false;
}

void Timer::PAUSE() {
	if (is_started && !is_paused)
	{
		is_paused = true;
		paused_tick = SDL_GetTicks() - start_tick;
	}
}

void Timer::UNPAUSE() {

	if (is_paused)
	{
		is_paused = false;
		start_tick = SDL_GetTicks() - paused_tick;
		paused_tick = 0;
	}
}

int Timer::get_ticks() {
	if (is_started)
	{
		if (is_paused) {
			return paused_tick;
		}
		else {
			return SDL_GetTicks() - start_tick;
		}
	}
}

bool Timer::IS_STARTED() { return is_started; }
bool Timer::IS_PAUSED() { return is_paused; }