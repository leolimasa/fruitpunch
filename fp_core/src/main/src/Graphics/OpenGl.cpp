/*
 * Gles2.cpp
 *
 *  Created on: 2012-02-19
 *      Author: leo
 */

#include <armadillo>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

#ifndef WIN32
#include <GL/glx.h>
#endif

#include <fruitpunch/Graphics/Vertex.h>
#include <fruitpunch/Graphics/OpenGl.h>
#include <fruitpunch/Graphics/Matrices.h>
#include <fruitpunch/Common/Runtime.h>

using namespace arma;
using namespace std;
using namespace fp_core::common;

namespace fp_core {

GLuint loadShader(GLenum shaderType, const char* source) {
	// Create shader object
	GLuint shader = glCreateShader(shaderType);

	// loads the source into the shader and compiles it
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	// Checks for compile errors
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		// An error happened, first retrieve the length of the log message.
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		// Allocate enough space for the message and retrieve it.
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetShaderInfoLog(shader, i32InfoLogLength, &i32CharsWritten,
				pszInfoLog);

		char* pszMsg = new char[i32InfoLogLength + 256];
		//sprintf_s( pszMsg, "Failed to compile fragment shader: %s", pszInfoLog );
		printf(pszMsg);
		return 0;
	}
	return shader;
}

OpenGl::OpenGl() {
	// TODO Auto-generated constructor stub

}

// ____________________________________________________________________________

void OpenGl::addTexture(Image& image) {

	// sets how the pixels are packed inside the texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// generates an OpenGl texture id
	unsigned int texid;
	glGenTextures(1, &texid);

	// selects the texture
	glBindTexture(GL_TEXTURE_2D, texid);

	// sets the repeating
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// uploads the texture to the video card
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(),
			0, GL_RGBA, GL_UNSIGNED_BYTE, image.rawData());

	// sets the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// ----------- test texture ---------------------
//  unsigned char pixels[4 * 3] = { 255, 0, 0, // Red
//              0, 255, 0, // Green
//              0, 0, 255, // Blue
//              255, 255, 0 // Yellow
//              };
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2,s
//        0,GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// If the PNG image has an alpha channel, we will need to setup blending.
	glEnable( GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// adds the newly created image to the map
	image.setTextureId(texid);
	image.setTextureLoaded(true);
}

// ____________________________________________________________________________

void OpenGl::removeTexture(Image& image) {
	unsigned int texid = image.getTextureId();
	glDeleteTextures(1, &texid);
	image.setTextureLoaded(false);
}

// ____________________________________________________________________________

/**
 * Initializes the viewport and compiles the shaders
 */
void OpenGl::init(int width, int height) {
	glewInit();

	static const char gVertexShader[] = "attribute vec4 a_position;   \n"
			"attribute vec2 a_texCoord;   \n"
			"varying vec2 v_texCoord;     \n"
			"void main()                  \n"
			"{                            \n"
			"   gl_Position = a_position; \n"
			"   v_texCoord = a_texCoord;  \n"
			"}                            \n";

	static const char gFragmentShader[] =
			"precision mediump float;                                \n"
					"varying vec2 v_texCoord;                                \n"
					"uniform sampler2D s_texture;                            \n"
					"uniform float a_alpha;"
					"void main() {                                           \n"
					"	gl_FragColor = texture2D(s_texture, v_texCoord);     \n"
					"   gl_FragColor.a *= a_alpha;                           \n"
					"  //gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);        	 \n"
					"}";

	// Initialize the vertex shader
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, gVertexShader);

	// Initialize the fragment shader
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, gFragmentShader);

	// Creates the GL program
	m_program = glCreateProgram();

	// Attaches the shaders to the program
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);

	// Link the program
	glLinkProgram(m_program);

	// Loads our program
	glUseProgram(m_program);

	// Gets where OpenGL has pointed the vPosition variable in the vertex shader
	// so we can send vertex through this variable later

	m_vPosition = glGetAttribLocation(m_program, "a_position");
	m_texCoord = glGetAttribLocation(m_program, "a_texCoord");
	m_alpha = glGetUniformLocation(m_program, "a_alpha");

	// Create the viewport
	glViewport(0, 0, width, height);

	// ---------------------------------------------------------------------------
	// Texture initialization
	// ---------------------------------------------------------------------------
	glEnable(GL_TEXTURE_2D);

	// Sets the s_texture shader variable to the first texture unit.
	GLuint loc = glGetUniformLocation(m_program, "s_texture");
	glUniform1i(loc, 0);

	// ---- Creates the viewport matrix ----
	//
	// OpenGl renders coordinates where x and y
	// are between -1 and 1. But we want it to be
	// between 0 and width or height of the screen
	// so we can position things with pixel coordinates.
	// This matrix will get a point given in pixels
	// and transform to a point in OpenGl coordinates.

	// scale it down so coordinates are between -1 and 1.
	// We use the 2.0f because thats how many units there
	// are between -1 and 1.
	point scale;
	scale.x = 2.0f / (float) width;
	scale.y = 2.0f / (float) height;
	fmat33 viewport = scale_matrix(scale);

	// translate it so it begins at the right corner
	point trans;
	trans.x = -1;
	trans.y = -1;
	viewport = (arma::fmat33) (translation_matrix(trans) * viewport);

	// flips the Y axis
	point flip;
	flip.x = 1;
	flip.y = -1;
	viewport = (arma::fmat33) (scale_matrix(flip) * viewport);

	m_viewport_matrix = viewport;
}

// ____________________________________________________________________________

/**
 * Clears the screen before rendering a primitive
 */
void OpenGl::pre_render() {
	// erases the framebuffer (screen) with a solid color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// clear buffers
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Loads our program
	//glUseProgram(m_program);
}

// ____________________________________________________________________________

void OpenGl::post_render() {
	glFlush();
}

// ____________________________________________________________________________

/**
 * Gets a array of floats from the primitive and renders its vertices
 */
void OpenGl::render_polygon(float * float_array, float * uv_array, int vertices,
		Image& image, float alpha) {

	// ---------------------------------------------------------------------------
	// Vertex Data
	// ---------------------------------------------------------------------------

	// Describes how OpenGL should read our vertices array
	glVertexAttribPointer(m_vPosition, 2, GL_FLOAT, GL_FALSE, 0, float_array);

	// Associate the vertex shader with the primitive
	glEnableVertexAttribArray(m_vPosition);

	//-------------------------------------------------------------------------------
	// Fragment Data (Fragment Shader Shit)
	//-------------------------------------------------------------------------------

	// make all of those fuckers change opacity
	glUniform1f(m_alpha, alpha);

	// ---------------------------------------------------------------------------
	// Loads in the texture
	// ---------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, image.getTextureId());

	glEnableVertexAttribArray(m_texCoord);
	glVertexAttribPointer(m_texCoord, 2, GL_FLOAT, GL_FALSE, 0, uv_array);

	// Draws the polygon
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

}

// ____________________________________________________________________________

point OpenGl::transform_point(point p, fmat33 trans_matrix) {

	// creates the matrix the represents the vertex
	fmat::fixed<3, 1> vmat;
	vmat << p.x << endr << p.y << endr << 1 << endr;

	// transform the vertex by multiplying its matrix by the transformation matrix
	fmat res = trans_matrix * vmat;

	// updates the vertex with the new transformation
	point newpos;
	newpos.x = res.at(0, 0);
	newpos.y = res.at(1, 0);
	return newpos;
}

// ____________________________________________________________________________

void OpenGl::unload() {
	// from the examples...will need modifications though...

	//UserData *userData = esContext->userData;

	// Delete texture object
	//glDeleteTextures ( 1, &userData->baseMapTexId );
	//glDeleteTextures ( 1, &userData->lightMapTexId );
	//glDeleteTextures ( 1, &userData->smileyMapTexId );

	// Delete program object
	//glDeleteProgram ( userData->programObject );
}

OpenGl::~OpenGl() {
}

fmat33 OpenGl::viewport() {
	return m_viewport_matrix;
}


std::string OpenGl::getGlError(int error) {
	std::string meaning;
	switch (error) {
	case GL_INVALID_ENUM:
		meaning = "GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		meaning = "GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		meaning = "GL_INVALID_OPERATION";
		break;
	case GL_OUT_OF_MEMORY:
		meaning = "GL_OUT_OF_MEMORY";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		meaning = "INVALID_FRAMEBUFFER_OPERATION";
		break;
	case GL_STACK_OVERFLOW:
		meaning = "STACK_OVERFLOW";
		break;
	case 0:
		meaning = "no error";
		break;
	default:
		meaning = "unknown error";
		break;
	}

	return meaning;
}

void OpenGl::printGlError() {
	GLenum error = glGetError();
	if (error != 0) {
		printf("OpenGL error: %s\n", getGlError(error).c_str());
	}
}

}

/* namespace fp_core */


