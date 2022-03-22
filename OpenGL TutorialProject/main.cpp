#include<iostream>
#include"GL/glew.h"
#include"Display.h"
#include"Mesh.h"
#include"Shader.h"
#include "Texture.h"
#include"Transform.h"
#include"Camera.h"

#define WIDTH  800
#define HEIGHT 600
int main(int argc, char **argv)
{

	//std::cout << "www.oxox.work" << std::endl;

	Display display(800,600,"www.oxox.work");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0),glm::vec2(0,0)),
		Vertex(glm::vec3(0,0.5,0),glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5,-0.5,0),glm::vec2(1.0,0)),};

	unsigned int indices[] = {0,1,2};
	Mesh mesh(vertices,sizeof(vertices)/sizeof(vertices[0]),
		indices,sizeof(indices)/sizeof(indices[0]));

	Mesh mesh2("./res/monkey3.obj");
	Shader shader("./res/basicShader");

	Texture texture("./res/container.jpg");
	Camera camera(glm::vec3(0,0,-4),180.0f,(float)WIDTH / (float) HEIGHT ,0.01f,1000.0f);
	Transform transform;
	float counter = 0.0f;
	while (!display.IsClosed())
	{
		
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		transform.GetPos()->x = sinCounter;
		//transform.GetPos()->z = sinCounter;
		transform.GetRot()->x = cosCounter * 1;
		//transform.GetRot()->y = cosCounter * 50;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		//transform.GetRot()->z = counter * 10;

		shader.Bind();

		texture.Bind();

		shader.Update(transform,camera);
		mesh2.Draw();

		display.Update();

		counter += 0.0005f;
		
	}
	return 0;
}