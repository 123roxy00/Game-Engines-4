#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 colour;
};

class Mesh
{
public:	
	Mesh(std::vector<Vertex>& vertexList_, GLuint textureID_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, glm::mat4 transform_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	std::vector<Vertex> vertexList;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc, viewPosLoc, lightPosLoc, lightAmbLoc, lightDiffLoc, lightSpecLoc, lightColLoc;
	GLuint viewPos;
	GLuint lightPos;
	GLuint lightAmb;
	GLuint lightDiff;
	GLuint lightSpec;
	GLuint lightCol;
};

#endif // !MESH_H