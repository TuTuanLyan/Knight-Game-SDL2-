//
//  Timer.h
//  Knight's Challenge Game
//
//  Created by Nguyen Tu Anh Tuan.
//

#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "Common_Items.h"

class Timer
{
public:
	Timer();
	~Timer();

	void START();
	void STOP();
	void PAUSE();
	void UNPAUSE();

	int get_ticks();

	bool IS_STARTED();
	bool IS_PAUSED();

private:
	int start_tick;
	int paused_tick;

	bool is_paused;
	bool is_started;

};

#endif // TIMER_H

