#ifndef IDV_GLDRIVER_H
#define IDV_GLDRIVER_H

#include <IDVVideo/IDVBaseDriver.h>

#include <GL/glew.h>
#include <SDL/SDL.h>

class IDVGLDriver : public IDVBaseDriver {
public:
	IDVGLDriver() : IDVBaseDriver(IDVAPI::OPENGL) {}
	void	InitDriver();
	void	CreateSurfaces();
	void	DestroySurfaces();
	void	Update();
	void	DestroyDriver();
	void	SetWindow(void *window) ;
	void	SetDimensions(int, int);

	int			CreateShader(std::string src_vs, std::string src_fs, unsigned int sig);
	IDVShaderBase*	GetShaderSig(unsigned int sig);
	IDVShaderBase*	GetShaderIdx(int Id);
	void		DestroyShaders();

	void	Clear();
	void	SwapBuffers();
	bool	CheckExtension(std::string s);

	GLint				CurrentFBO;
	GLenum				DrawBuffers[16];

	int	width, height;
	std::vector<std::string>	ExtensionsTok;
	std::string					Extensions;
};

#endif
