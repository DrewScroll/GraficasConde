
#ifndef IDV_GLSHADER_H
#define IDV_GLSHADER_H

#include <IDVVideo/IDVBaseDriver.h>

#include <GL/glew.h>
#include <SDL/SDL.h>


class IDVGLShader : public IDVShaderBase {
public:
	IDVGLShader() {
		matWorldViewProjUniformLoc = -1;
		matWorldUniformLoc = -1;

		vertexAttribLoc = -1;
		normalAttribLoc = -1;
		tangentAttribLoc = -1;
		binormalAttribLoc = -1;
		uvAttribLoc = -1;
		uvSecAttribLoc = -1;

		Light0Pos_Loc = -1;
		Light0Color_Loc = -1;
		CameraPos_Loc = -1;
		Ambient_loc = -1;
		DiffuseTex_loc = -1;
		SpecularTex_loc = -1;
		GlossTex_loc = -1;
		NormalTex_loc = -1;
		ReflectTex_loc = -1;

		tex0_loc = -1;
		tex1_loc = -1;
		tex2_loc = -1;
		tex3_loc = -1;
		tex4_loc = -1;
		tex5_loc = -1;
		tex6_loc = -1;
		tex7_loc = -1;
	}

	virtual ~IDVGLShader() {}

	bool CreateShaderAPI(std::string src_vs, std::string src_fs, unsigned int sig);

	unsigned int ShaderProg;

	int			 matWorldViewProjUniformLoc;
	int			 matWorldUniformLoc;
	int			 matWorldViewUniformLoc;
	int			 matWVPInverseUniformLoc;
	int		     matWVPLightLoc;

	int			 vertexAttribLoc;
	int			 normalAttribLoc;
	int			 tangentAttribLoc;
	int			 binormalAttribLoc;
	int			 uvAttribLoc;
	int			 uvSecAttribLoc;

	int			Light0Pos_Loc;
	int			Light0Color_Loc;

	int			LightPositions_Loc;
	int			LightColors_Loc;

	int			CameraPos_Loc;
	int			CameraInfo_Loc;

	int			LightCameraPos_Loc;
	int			LightCameraInfo_Loc;

	int			Ambient_loc;

	int			DiffuseTex_loc;
	int			SpecularTex_loc;
	int			GlossTex_loc;
	int			NormalTex_loc;
	int			ReflectTex_loc;

	int			tex0_loc;
	int			tex1_loc;
	int			tex2_loc;
	int			tex3_loc;
	int			tex4_loc;
	int			tex5_loc;
	int			tex6_loc;
	int			tex7_loc;

	int			texEnv_loc;
};


#endif
