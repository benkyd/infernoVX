#ifndef INFERNOVX_RENDERPASS_H_
#define INFERNOVX_RENDERPASS_H_

#include "rasterbuffer.hpp"

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

	GLuint VBO, VAO;

	RasterRenderer RasterPass;

private:

	// is now owned
	Camera* mCamera;

	// is owned
	Scene* mScene;

};

class RenderPass
{
public:



};

#endif
