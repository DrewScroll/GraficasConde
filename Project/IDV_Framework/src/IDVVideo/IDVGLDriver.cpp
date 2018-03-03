
#include <IDVVideo/IDVGLDriver.h>
#include <IDVVideo/IDVGLShader.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

void	IDVGLDriver::InitDriver() {

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		printf("Error: %s\n", glewGetErrorString(err));
	}
	else {
		printf("GLEW OK\n");
	}
	SDL_Surface *sur = SDL_GetVideoSurface();
	width = sur->w;
	height = sur->h;

	std::string GL_Version = std::string((const char*)glGetString(GL_VERSION));
	std::string GL_Extensions = std::string((const char*)glGetString(GL_EXTENSIONS));

	std::istringstream iss(GL_Extensions);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };

	ExtensionsTok = tokens;
	Extensions = GL_Extensions;

	std::cout << "GL Version: " << GL_Version << "\n\nExtensions\n\n";

	for (unsigned int i = 0; i < ExtensionsTok.size(); i++) {
		printf("[%s]\n", ExtensionsTok[i].c_str());
	}

	const unsigned char *version  = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("GLSL Ver: %s \n",version);

	glEnable(GL_DEPTH_TEST);
	glClearDepthf(1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &CurrentFBO);

	for (int i = 0; i < 16; i++) {
		DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
	}

}

void	IDVGLDriver::CreateSurfaces() {

}

void	IDVGLDriver::DestroySurfaces() {

}

void	IDVGLDriver::Update() {

}

void	IDVGLDriver::DestroyDriver() {

}

void	IDVGLDriver::SetWindow(void *window) {

}

void	IDVGLDriver::SetDimensions(int w, int h){
    width = w;
    height = h;
}

void	IDVGLDriver::Clear() {
	glClearColor(0.5,0.0,0.5,1.0);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

}

void	IDVGLDriver::SwapBuffers() {
	SDL_GL_SwapBuffers();
}

bool IDVGLDriver::CheckExtension(std::string s){
	return (Extensions.find(s) != std::string::npos);
}

int IDVGLDriver::CreateShader(std::string src_vs, std::string src_fs, unsigned int sig) {
	for (unsigned int i = 0; i < Shaders.size(); i++) {
		if (Shaders[i]->Sig == sig) {
			return i;
		}
	}

	IDVGLShader* shader = new IDVGLShader();
	if (shader->CreateShader(src_vs, src_fs, sig)) {
		Shaders.push_back(shader);
		return (Shaders.size() - 1);
	}
	else {
		delete shader;
	}
	return -1;
}

IDVShaderBase*	IDVGLDriver::GetShaderSig(unsigned int sig) {
	for (unsigned int i = 0; i < Shaders.size(); i++) {
		if (Shaders[i]->Sig == sig) {
			return Shaders[i];
		}
	}
	return 0;
}

IDVShaderBase*	IDVGLDriver::GetShaderIdx(int id) {
	if (id < 0 || id >= (int)Shaders.size()) {
		printf("Warning null ptr ShaderBase Idx\n");
		return 0;
	}

	return Shaders[id];
}

void IDVGLDriver::DestroyShaders() {
	for (unsigned int i = 0; i < Shaders.size(); i++) {
		IDVGLShader *pShader = dynamic_cast<IDVGLShader*>(Shaders[i]);
		delete pShader;
	}
}
