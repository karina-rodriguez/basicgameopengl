#include "GameObject.hpp"

GameObject::GameObject() {
	transformation = glm::mat4(1.0);
	visible = 1;
}
GameObject::~GameObject() {
}
void GameObject::loadObject(char *filename) {


	bool res = loadAssImp(filename, indices, vertices, uvs, normals);

}
void GameObject::setColor(glm::vec3 colort) {

	for (int i = 0; i < vertices.size(); i++) {
		colors.push_back(colort);
	}
}
void GameObject::calculateBoundingBox() {
	boundingbox_min.x = boundingbox_max.x = vertices[0].x;
	boundingbox_min.y = boundingbox_max.y = vertices[0].y;
	boundingbox_min.z = boundingbox_max.z = vertices[0].z;
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].x < boundingbox_min.x) boundingbox_min.x = vertices[i].x;
		if (vertices[i].x > boundingbox_max.x) boundingbox_max.x = vertices[i].x;
		if (vertices[i].y < boundingbox_min.y) boundingbox_min.y = vertices[i].y;
		if (vertices[i].y > boundingbox_max.y) boundingbox_max.y = vertices[i].y;
		if (vertices[i].z < boundingbox_min.z) boundingbox_min.z = vertices[i].z;
		if (vertices[i].z > boundingbox_max.z) boundingbox_max.z = vertices[i].z;
	}


}

std::vector<unsigned short> GameObject::getIndices() {
	return indices;
}
std::vector<glm::vec3> GameObject::getVertices() {
	return vertices;
}

std::vector<glm::vec3> GameObject::getColors() {
	return colors;
}
std::vector<glm::vec2> GameObject::getUVs() {
	return uvs;
}
std::vector<glm::vec3> GameObject::getNormals() {
	return normals;
}
GLuint* GameObject::getVertexbuffer() {
	return &vertexbuffer;
}	
GLuint* GameObject::getColorbuffer() {
	return &colorbuffer;
}
GLuint* GameObject::getNormalbuffer() {
	return &normalbuffer;
}


void GameObject::setInitialPosition(glm::vec3 initial_post) {
	initial_pos = initial_post;
	position = initial_pos;
	
}
void GameObject::updateBoundingBox() {
	boundingbox_min = boundingbox_min + position;
	boundingbox_max = boundingbox_max + position;
}
glm::vec3 GameObject::getInitialPosition() {
	return initial_pos;
}

glm::vec3 GameObject::getPosition() {
	return position;
}
void GameObject::updatePosition(glm::vec3 move) {
	position = position + move;

	boundingbox_min = boundingbox_min + move;
	boundingbox_max = boundingbox_max + move;
}
void GameObject::setTransformation(glm::mat4 transformationt) {
	transformation = transformationt;

}
glm::mat4 GameObject::getTransformation() {
	return transformation;
}

bool GameObject::hasCollided(GameObject* collided) {
	if (
		//first condition check in Z
		((((boundingbox_min.z > collided->getBoundingBoxMin().z) && 
		(boundingbox_min.z < collided->getBoundingBoxMax().z)) ||
		(((boundingbox_max.z > collided->getBoundingBoxMin().z) &&
		(boundingbox_max.z < collided->getBoundingBoxMax().z)))) && 
		//second condition check in X
		(((boundingbox_min.x > collided->getBoundingBoxMin().x) &&
		(boundingbox_min.x < collided->getBoundingBoxMax().x)) ||
		(((boundingbox_max.x > collided->getBoundingBoxMin().x) &&
		(boundingbox_max.x < collided->getBoundingBoxMax().x))))) ||
		//another option will be to check the bounding box centre
		((((boundingbox_min.z+boundingbox_max.z)/2 > collided->getBoundingBoxMin().z) &&
		((boundingbox_min.z + boundingbox_max.z) / 2 < collided->getBoundingBoxMax().z)) &&
		((((boundingbox_min.x + boundingbox_max.x) / 2 > collided->getBoundingBoxMin().x) &&
		((boundingbox_min.x + boundingbox_max.x) / 2 < collided->getBoundingBoxMax().x))))
		) {
		return true;
	}
	else return false;
}
glm::vec3 GameObject::getBoundingBoxMin() {
	return boundingbox_min;
}
glm::vec3 GameObject::getBoundingBoxMax(){
	return boundingbox_max;

}


bool GameObject::isVisible() {
	return visible;
}
void GameObject::setVisible(bool is) {
	visible = is;
}
