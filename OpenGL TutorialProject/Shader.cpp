#include "Shader.h"
#include<iostream>
#include<fstream>

static GLuint CreateShader(const std::string & text, GLenum shaderType);

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage);
//加载着色器文件，并返回着色器的所有内容
static std::string LoadShader(const std::string & fileName);


Shader::Shader(const std::string & fileName)
{
	m_pragram = glCreateProgram();
	
	//std::cout << glGetString(GL_VERSION) << std::endl;
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"),GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"),GL_FRAGMENT_SHADER);

	for (unsigned int i = 0;i < NUM_SHADERS; i++)
	{
		glAttachShader(m_pragram,m_shaders[i]);
	}
	glBindAttribLocation(m_pragram,0,"position");
	glBindAttribLocation(m_pragram, 1, "texCoord");
	glLinkProgram(m_pragram);
	CheckShaderError(m_pragram,GL_LINK_STATUS,true,"Error:Program Linking invalid");

	glValidateProgram(m_pragram);
	CheckShaderError(m_pragram, GL_VALIDATE_STATUS, true, "Error:Program Validate invalid");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_pragram,"transform");
}
Shader::~Shader()
{
	for (unsigned int i = 0;i < NUM_SHADERS; i++)
	{
		glAttachShader(m_pragram, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_pragram);
}
void Shader::Bind()
{
	glUseProgram(m_pragram);
}
void Shader::Update(const Transform & transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U],1,GL_FALSE,&model[0][0]);
}
static GLuint CreateShader(const std::string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr<< "Erro: Shader creation failure!" <<std::endl;
	}
	const  GLchar * shaderSourceString[1];

	GLint shaderSourceStringLength[1];

	shaderSourceString[0] = text.c_str();

	shaderSourceStringLength[0] = text.length();

	glShaderSource(shader ,1 ,shaderSourceString,shaderSourceStringLength);
	glCompileShader(shader);
	
	
	CheckShaderError(shader,GL_COMPILE_STATUS,false,"ERROR:Shader compilation failed");

	return  shader;

}
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if (isProgram)
	{
		glGetProgramiv(shader,flag,&success);
	}
	else
	{
		glGetShaderiv(shader, flag,&success);
	}
	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader,sizeof(error),NULL,error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ":" << error << std::endl;
	}
}
static std::string LoadShader(const std::string & fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::cout << (fileName).c_str() << std::endl;
	std::string output;
	std::string line;

	if(file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader:" << fileName << std::endl;
	}

	return output;
}