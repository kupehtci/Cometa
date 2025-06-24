
#ifndef COMETA_TIME_H
#define COMETA_TIME_H

#include "./Singleton.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"

class Time : public SingletonManager<Time> {

private:
	// Time between previous frame and this one
	float _deltaTime;

	// scale of time that can be used to modify delta time and change speed of the execution
	float _timeScale;

	// utils
	float _lastFrameTime;

public: 
	Time();
	~Time() override = default;

	/**
	 * Init the time manager
	 */
	void Init() override;

	/**
	 * Update the time manager
	 * Updates the delta time and other parameters
	 */
	void Update() override;

	/**
	 * Close the time manager
	 */
	void Close() override;


private: 
	void UpdateDeltaTime(); 

	// --------- GETTERS AND SETTERS ---------
public: 
	float inline static GetDeltaTime() { return Time::GetInstancePtr()->_deltaTime; }

	float inline static GetTimeScale() { return Time::GetInstancePtr()->_timeScale; }
};


#endif // COMETA_TIME_H