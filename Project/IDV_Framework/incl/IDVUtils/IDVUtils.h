#ifndef IDV_UTILS_GL_H
#define IDV_UTILS_GL_H

#include <stdio.h>
#include <iostream>
#include <string>

#include <GL/glew.h>

void checkcompilederrors(GLuint shader, GLenum type);
void CheckGLError();
void CheckFBStatus();
GLuint createShader(GLenum type, char* pSource);


char *file2string(const char *path);
std::string RemovePath(std::string p);

#endif
