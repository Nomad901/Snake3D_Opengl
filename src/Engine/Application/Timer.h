#pragma once
#include <iostream>
#include <chrono> 
#include <mutex>

class Timer
{
public:
	enum class DimensionOfTime
	{
		NANOSECONDS = 0,
		MILISECONDS = 1,
		SECONDS		= 2,
		MINUTES		= 3
	};
public:
	void startTimer(DimensionOfTime pDimensionOfTime = DimensionOfTime::MILISECONDS);
	void stopTimer();
	
	bool isRunning() noexcept;

	// *****************
	// Stops timer and returns delta time;
	// *****************
	float getDeltaTime();

private:
	enum class TimerStates
	{
		TIMER_STARTED = 0,
		TIMER_STOPPED = 1,
		TIMER_IDLE	  = 2
	};
private:
	TimerStates mCurrentTimerState{ TimerStates::TIMER_IDLE };
	
	DimensionOfTime mDimensionOfTime{ DimensionOfTime::MILISECONDS };
	std::chrono::time_point<std::chrono::high_resolution_clock> mStartTimer, mEndTimer;

	std::mutex mMutex;
};

