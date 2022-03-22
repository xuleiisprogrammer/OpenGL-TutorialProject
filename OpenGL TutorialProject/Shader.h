#pragma once

#include <string>
#include <GL/glew.h>
#include"Transform.h"
#include"Camera.h"
class Shader
{
public:
	Shader(const std::string & fileName);

	void Bind();

	void Update(const Transform & transform,const Camera& camera);
	
	~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;
	enum 
	{
		TRANSFORM_U,
		NUM_UNIFORM
	};
	GLuint m_pragram;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORM];
};





