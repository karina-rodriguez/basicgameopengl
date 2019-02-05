#pragma once
#include "View.hpp"
#include "Model.hpp"
#include "global.hpp"

class Controller{
	public:
	//static int objectCount;
	///static int oldKeyState;
	//int newKeyState;


	private:
	Model* model;   // Model of game
	View*  view;    // View of game
	double deltaTime;
	double currentFrame;
	double lastFrame;
	double speed;

	public:
	
	Controller(Model* model, View *view);
	~Controller();

	void loop();

};
