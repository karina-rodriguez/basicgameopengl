#include "Model.hpp"


Model::Model()
{
   
	sprintf(text, "text goes here");
    
}
Model::~Model()
{
}
void Model::createGameObjects() {

	
	//create player
	player = new GameObject();
	player->loadObject((char*)"Assets/sphere.obj");
    player->setColor(glm::vec3(1.0,0.6, 0.0));
	player->calculateBoundingBox();
	player->setInitialPosition(glm::vec3(0, 0, 0));

}


GameObject*  Model::getPlayer() {
	return player;

}
void Model::updatePlayer(glm::vec3 move) {
	player->updatePosition(move);

}
char* Model::getText() {
    return text;
}
