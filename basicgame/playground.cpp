// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include "View.hpp"
#include "Model.hpp"
#include "Controller.hpp"
#include "global.hpp"
const int g_height = 500;
const int g_width = 1000;

int main(void)
{


	//initialise all
    Model* mymodel = new Model();
    View* myview = new View(mymodel);
    Controller* controller = new Controller(mymodel,myview);

    //create all thegames in the scene
    mymodel->createGameObjects();

    //initialise the scene and if succesful go into the control loop to wait for user input
    if (myview->initialise() != -1) {
        controller->loop();
    }    else {
        std::cout << "ERROR: The game has not been initialised correctly" << std::endl;
        return 0;
    }
    
   
    return 0;
}

