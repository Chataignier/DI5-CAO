#include <FrameCounter.h>
#include <Config.h>

int FrameCounter::frameCount = 0;

void FrameCounter::IncFrameCount()
{
	frameCount++; // une fenêtre de plus
}

void FrameCounter::DecFrameCount()
{
	// s'il n'y a plus de fenêtre ouverte, on termine le programme proprement
	frameCount--;
	if (frameCount == 0)
		wxTheApp->ExitMainLoop();
}
