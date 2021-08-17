#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

#include <GL/GLU.h>

#include "Globals.h"
#include <vector>


#include <noise/noise.h>
#include "noiseutils.h"
class HeightField {
public:

	

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;

	glm::vec3 position;


	bool Create(char *hFileName, const int hWidth, const int hHeight);
	bool CreateFromFractal(const int hWidth, const int hHeight);

	void Render(void);

	glm::mat4 terrainMVP;
	glm::mat4 modelM;

	void MoveRotateScale(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	//void SolidSphere(float basex, float basey, float r, int lats, int longs);
	void SolidSphere(double r, int lats, int longs);
	bool Init();

	unsigned char hHeightField[1024][1024];
	Graphics3D* G3d;

	int hmHeight;
	int hmWidth;

	GLuint tID[10];

	int bound;

	int hLOD;

	int VertexCount;

private:



};