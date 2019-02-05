#pragma once
#include "Model.hpp"
#include "GameObject.hpp"
#include <glm/gtx/transform.hpp>
#include "global.hpp"

class Model {
private: 
	
	GameObject* player;
    char text[256];
public:
    
Model();
	~Model();
    void createGameObjects();
	GameObject* getPlayer();
    void updatePlayer(glm::vec3 move);
    char* getText();
};
