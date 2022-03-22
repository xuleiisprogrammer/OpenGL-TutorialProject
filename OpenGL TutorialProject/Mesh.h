#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include<string>
#include"obj_loader.h"
class Vertex
{
public:
	Vertex(const glm::vec3& pos,const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }

	~Vertex() {};

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};


class Mesh
{
public:
	Mesh(Vertex * vertices,unsigned int numVertices,unsigned int* indices,unsigned int numIndices);

	Mesh(const std::string fileName);
	void Draw();
	~Mesh();

private:
	void InitMesh(const IndexedModel& model);
	enum {
		POSITION_VB,
		TexCOORD_VB,
		INDEX_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};













