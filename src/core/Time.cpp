#include "Time.h"


Time::Time() {
	_deltaTime = 0;
	_timeScale = 1.0f; 
	_lastFrameTime = 0.0f;
}

void Time::Init() {
	_lastFrameTime = (float)glfwGetTime();
}

void Time::Update() {

	UpdateDeltaTime(); 
}

void Time::Close() {
	
}


// Private Methods

void Time::UpdateDeltaTime() {
	float currentFrameTime = (float)glfwGetTime();
	_deltaTime = currentFrameTime - _lastFrameTime;
	_lastFrameTime = currentFrameTime;
}