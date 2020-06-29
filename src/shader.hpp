#ifndef INFERNOVX_SHADER_H_
#define INFERNOVX_SHADER_H_

#include <logger.h>

#include <glad/glad.h>

class Shader
{
public:
	Shader();

	void Load( std::string path );
	void Load( std::string path, GLenum type );

	GLuint Program;
	void Link();

	void Bind();
	void UnBind();

	~Shader();
private:
	std::unique_ptr<Logger> mLogger;

	bool mCheckShader( GLuint uid );

	GLuint mFrag;
	GLuint mVert;
};

#endif
