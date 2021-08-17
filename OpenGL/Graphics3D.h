#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Network.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Graphics3D
{
public:
	Graphics3D(void);
	void Init();
	void Draw();
	GLuint loadTexture(const char* theFileName);
	GLuint loadCubeMapTexture(const char* theFileName[6]);
	glm::mat4 getMVP();
	GLuint getVertexBuffer();
	GLuint getUvBuffer();
	GLuint getMatrixID();
	GLuint getTextureID();
	GLuint getBoolCubeMapID();
	GLuint getCubeMapTextureID();

	GLuint getTerrainTextureID(int);
	GLuint getTerrainMatrixID();
	GLuint getTerrainModelMatrixID();
	GLuint getTerrainViewMatrixID();
	GLuint getTerrainLightID();

	GLuint getLightTextureID();
	GLuint getLightMatrixID();
	GLuint getLightModelMatrixID();
	GLuint getLightViewMatrixID();
	GLuint getLightLightID();
	GLuint getTerrainTimeID();
	glm::mat4 getProjection();
	glm::mat4 getView();

private:



};

