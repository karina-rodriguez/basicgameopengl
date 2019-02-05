#include "View.hpp"

View::View(Model* modelt):model(modelt) {
	lightPosition = glm::vec3(-4, 8, 0);
	cameraPosition = glm::vec3(0, 0, 3);
}

View::~View() {

}
GLFWwindow* View::getWindow() {
	return window;
}

int View::initialise() {

    
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(g_width, g_height, "My Game", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
      glfwPollEvents();
    glfwSetCursorPos(window, g_width / 2, g_height / 2);
    
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

   	//glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
    
    //************************************
    //******* write in here the objects
    //************************************
    generateBuffers(model->getPlayer());

    
	programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");

	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");
	//GLuint ModelMatrix2ID = glGetUniformLocation(programID, "M2");

	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	CameraID = glGetUniformLocation(programID, "CameraPosition_worldspace");

	// Initialize our little text library with the Holstein font
	initText2D("Assets/Holstein.DDS");
	
    glfwSetWindowPos(window, 0, 0);

	return 1;
}
void View::generateBuffers(GameObject* go){
    glGenBuffers(1, go->getVertexbuffer());
    glBindBuffer(GL_ARRAY_BUFFER, *go->getVertexbuffer());
    glBufferData(GL_ARRAY_BUFFER, go->getVertices().size() * sizeof(glm::vec3), &go->getVertices()[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, go->getColorbuffer());
    glBindBuffer(GL_ARRAY_BUFFER, *go->getColorbuffer());
    glBufferData(GL_ARRAY_BUFFER, go->getColors().size() * sizeof(glm::vec3), &go->getColors()[0], GL_STATIC_DRAW);
    
    
    glGenBuffers(1, go->getNormalbuffer());
    glBindBuffer(GL_ARRAY_BUFFER, *go->getNormalbuffer());
    glBufferData(GL_ARRAY_BUFFER, go->getNormals().size() * sizeof(glm::vec3), &go->getNormals()[0], GL_STATIC_DRAW);
    
    
}
void View::update(char* text) {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(programID);

	
	glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(CameraID, cameraPosition.x, cameraPosition.y, cameraPosition.z);

	glm::mat4 ViewMatrix = glm::lookAt(
		cameraPosition, // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)(g_width/g_height), 0.1f, 100.0f);
    
    
//    glm::mat4 ModelMatrixPlayer =  glm::mat4(1.0);
    
   glm::mat4 ModelMatrixPlayer = glm::translate(model->getPlayer()->getPosition());
	glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrixPlayer;
    
    
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixPlayer[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	
    //************************************
    //******* update in here the objects
    //************************************
    updateObject(model->getPlayer());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	printText2D(text, 0,  550, 30);

	// Swap buffers
	glfwSwapBuffers(window);

}

void View::updateObject(GameObject* go){
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, *go->getVertexbuffer());
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, *go->getColorbuffer());
    glVertexAttribPointer(
                          1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 3nd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, *go->getNormalbuffer());
    glVertexAttribPointer(
                          2,                                // attribute
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
       glDrawArrays(GL_TRIANGLES, 0, go->getVertices().size());

    
}

void View::destroy() {

    destroyObject(model->getPlayer());
	

	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}


void View::destroyObject(GameObject* go) {
    // Cleanup VBO and shader
    glDeleteBuffers(1, go->getVertexbuffer());
    glDeleteBuffers(1, go->getColorbuffer());
    glDeleteBuffers(1, go->getNormalbuffer());

}
