#pragma once
// Include GLM
#include <glm/glm.hpp>
#include <vector>
#include "common/objloader.hpp"
#include <glm/gtx/transform.hpp>

class GameObject {
private:
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	
    GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint normalbuffer;

	glm::vec3 initial_pos;
	glm::vec3 position;
	glm::mat4 transformation;

	glm::vec3 boundingbox_min, boundingbox_max;
	bool visible;

	
public:
	GameObject();
	~GameObject();
	void loadObject(char *filename);
	std::vector<unsigned short> getIndices();
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getColors();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getNormals();
	GLuint* getVertexbuffer();
	GLuint* getNormalbuffer();
	GLuint* getColorbuffer();
	void setInitialPosition(glm::vec3 initial_pos);
	glm::vec3 getInitialPosition();
	glm::vec3 getPosition();
	void setColor(glm::vec3 colort);
	void calculateBoundingBox();
	void updateBoundingBox();
	glm::vec3 getBoundingBoxMin();
	glm::vec3 getBoundingBoxMax();



	void updatePosition(glm::vec3 move);
	void setTransformation(glm::mat4 transformation);
	glm::mat4 getTransformation();
	bool hasCollided(GameObject* collided);
	bool isVisible();
	void setVisible(bool is);

};
