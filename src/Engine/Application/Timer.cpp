#include "Timer.h"

void Timer::startTimer(DimensionOfTime pDimensionOfTime)
{
	std::lock_guard<std::mutex> guard(mMutex);
	mCurrentTimerState = TimerStates::TIMER_STARTED;
	mStartTimer = std::chrono::high_resolution_clock::now();
}

void Timer::stopTimer()
{
	std::lock_guard<std::mutex> guard(mMutex);
	if (mCurrentTimerState != TimerStates::TIMER_IDLE)
	{
		mCurrentTimerState = TimerStates::TIMER_STOPPED;
		mEndTimer = std::chrono::high_resolution_clock::now();
	}
}

bool Timer::isRunning() noexcept
{
	return mCurrentTimerState == TimerStates::TIMER_STARTED;
}

float Timer::getDeltaTime()
{
	using namespace std::chrono;

	switch (mCurrentTimerState)
	{
	case Timer::TimerStates::TIMER_STARTED:
		stopTimer();
		break;
	case Timer::TimerStates::TIMER_STOPPED:
		break;
	case Timer::TimerStates::TIMER_IDLE:
		return 0.0f;
	}
	
	mCurrentTimerState = TimerStates::TIMER_IDLE;

	switch (mDimensionOfTime)
	{
	case Timer::DimensionOfTime::NANOSECONDS:
		return static_cast<float>(duration_cast<nanoseconds>(mEndTimer - mStartTimer).count());
	case Timer::DimensionOfTime::MILISECONDS:
		return static_cast<float>(duration_cast<milliseconds>(mEndTimer - mStartTimer).count());
	case Timer::DimensionOfTime::SECONDS:
		return static_cast<float>(duration_cast<seconds>(mEndTimer - mStartTimer).count());
	case Timer::DimensionOfTime::MINUTES:
		return static_cast<float>(duration_cast<minutes>(mEndTimer - mStartTimer).count());
	}

	return 0.0f;
}
