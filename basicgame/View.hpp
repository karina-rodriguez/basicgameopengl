#pragma once
// Include GLEW
#include <GL/glew.h>
#include "Model.hpp"

// Include GLFW
#include <glfw3.h>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include <glm/gtx/transform.hpp>
#include "common/shader.hpp"
#include "common/controls.hpp"
#include "common/text2D.hpp"

class View {
private:
	Model* model;
	GLFWwindow* window;

	GLuint programID;
	GLuint MatrixID;
	GLuint LightID;
	GLuint CameraID;

	GLuint ViewMatrixID;
	GLuint ModelMatrixID;

	GLuint VertexArrayID;
	
	bool isDrawBoundingBox;

	glm::vec3 lightPosition;
	glm::vec3 cameraPosition;

//	int rotationcounter=0;



public:
	View(Model* modelt);
    
	~View();
	GLFWwindow* getWindow();
    int initialise();
    void generateBuffers(GameObject* go);
        
	void drawBoundingBox(GameObject* goBoundingBox, glm::mat4 projectionMatrix, glm::mat4 ViewMatrix);

	void update(char* text);
    void updateObject(GameObject* go);
	void destroy();
    void destroyObject(GameObject* go);
        

};
