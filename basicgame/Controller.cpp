#include "Controller.hpp"

Controller::Controller(Model* modelt, View *viewt):model(modelt),view(viewt)
{
	
	currentFrame = glfwGetTime();
	speed = 0.0005;
}

Controller::~Controller()
{

}
void Controller::loop() {
	
	//this is the main loop while the game is "running"
	do {
		
	
		if (glfwGetKey(view->getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
			 model->updatePlayer(glm::vec3(0, speed, 0));
		if (glfwGetKey(view->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
			 model->updatePlayer(glm::vec3(speed, 0, 0));
		if (glfwGetKey(view->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
            model->updatePlayer(glm::vec3(-speed, 0, 0));
			
		if (glfwGetKey(view->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
            model->updatePlayer(glm::vec3(0, -speed,0));
			
        
        
        deltaTime = currentFrame - lastFrame;
        lastFrame = glfwGetTime();
        
        view->update(model->getText());
        
        
		glfwPollEvents();
	}
	// Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(view->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(view->getWindow()) == 0);

	view->destroy();


}
