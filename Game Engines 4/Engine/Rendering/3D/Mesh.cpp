#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), 
VBO(0), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0), 
textureLoc(0), viewPosLoc(0), lightPosLoc(0), lightAmbLoc(0),
lightDiffLoc(0), lightSpecLoc(0), lightColLoc(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0)
		subMesh.vertexList.clear();

	if (subMesh.meshIndices.size() > 0)
		subMesh.meshIndices.clear();
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

	glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetPosition()));
	glUniform1f(lightAmbLoc, camera_->GetLightSources()[0]->GetAmbient());
	glUniform1f(lightDiffLoc, camera_->GetLightSources()[0]->GetDiffuse());
	glUniform1f(lightSpecLoc, camera_->GetLightSources()[0]->GetSpecular());
	glUniform3fv(lightColLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetLColour()));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);
	
	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	//Tex Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));
	//Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	viewPosLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.Position");
	lightAmbLoc = glGetUniformLocation(shaderProgram, "light.Ambient");
	lightDiffLoc = glGetUniformLocation(shaderProgram, "light.Diffuse");
	lightSpecLoc = glGetUniformLocation(shaderProgram, "light.Specular");
	lightColLoc = glGetUniformLocation(shaderProgram, "light.Colour");
}