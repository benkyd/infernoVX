#ifndef INFERNOVX_RENDERPASS_H_
#define INFERNOVX_RENDERPASS_H_

#include "rasterbuffer.hpp"
#include "shader.hpp"

class Camera;
class Display;

class Scene;

class Pipeline
{
public:

	// does not pass ownership
	Pipeline( Display* display, Camera* camera );

	// does not pass ownership
	void NextFrame( Display* display );

	GLuint VBO, VAO, EBO;

	RasterBuffer GBuffer;
	Shader DefferedShader;
	Shader DrawQuadShader;

private:

	// is not owned
	Camera* mCamera;

	// is owned
	Scene* mScene;

};

class RenderPass
{
public:



};

#endif
